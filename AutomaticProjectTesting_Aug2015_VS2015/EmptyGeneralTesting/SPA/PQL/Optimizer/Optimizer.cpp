#include <cassert>
#include <algorithm>

#include "Optimizer.h"
#include "ClauseGroupManager.h"
#include "ClauseGroup.h"
#include "../Utilities/Clause.h"
#include "SynonymUFDS.h"
#include "ClauseCostCalculator.h"

Optimizer::Optimizer(QueryTree &queryTree)
{
    /*
        Process description:
        1. Populates and initialises internal data structures
        2. Split clauses into groups
        3. Sort clauses within groups for efficient evaluation
        4. Sort clause groups for efficient evaluation
    */
    processQueryTree(queryTree);
    extractSelectedSyns(queryTree);
    formClauseGroups();
    sortClauseGroups();
    _clauseGroupsManager.setClauseGroupQueue(createClauseGroupQueue());
}

/*
    Gets a ClauseGroupManager object that contains processed clause groups
    for efficient evaluation and handles evaluated results of clause groups.
*/
ClauseGroupManager Optimizer::getClauseGroupManager()
{
    return _clauseGroupsManager;
}

/*
    Loops through all clauses in a query tree and updates the appropriate data
    structures in Optimizer.
*/
bool Optimizer::processQueryTree(QueryTree &queryTree)
{
    _clauseGroupsManager.setSelectedSynonyms(queryTree.getSelectClause().getSynonyms());

    list<ClausePtr> allClauses = extractClausesFromQueryTree(queryTree);

    for (ClausePtr clause : allClauses) {

        _clauseVector.push_back(clause);
        int clauseIdx = _clauseVector.size() - 1;   // Clause just added should be the last element

        // Assign index to each new synonyms
        list<string> synonyms = clause->getSynonyms();
        for (string synonym : synonyms) {

            if (_synToIdxMap.find(synonym) == _synToIdxMap.end()) {
                _synVector.push_back(synonym);
                int synIdx = _synVector.size() - 1;     // Synonym just added should be the last element
                _synToIdxMap[synonym] = synIdx;
            }
            _synIdxToClauseIdxsMap[_synToIdxMap[synonym]].push_back(clauseIdx);

        }

    }

    return true;
}

bool Optimizer::extractSelectedSyns(QueryTree& queryTree)
{
    list<string> selectedSyns = queryTree.getSelectClause().getSynonyms();
    _selectedSynonyms = unordered_set<string>{ selectedSyns.begin(), selectedSyns.end() };
    return true;
}

/*
    Extracts all clauses in a given QueryTree.
*/
list<ClausePtr> Optimizer::extractClausesFromQueryTree(QueryTree &queryTree)
{
    unordered_set<string> synsInNonSelectClauses;
    list<ClausePtr> allClauses;

    SelectClause selectClause = queryTree.getSelectClause();
    vector<SuchThatClause> suchThatClauses = queryTree.getSuchThatClauses();
    vector<PatternClause> patternClauses = queryTree.getPatternClauses();
    vector<WithClause> withClauses = queryTree.getWithClauses();

    for (SuchThatClause suchThatClause : suchThatClauses) {
        list<string> synonyms = suchThatClause.getSynonyms();
        synsInNonSelectClauses.insert(synonyms.begin(), synonyms.end());

        SuchThatClausePtr stPtr;
        stPtr = suchThatClause.getSharedPtr();
        allClauses.push_back(stPtr);
    }

    for (PatternClause patternClause : patternClauses) {
        list<string> synonyms = patternClause.getSynonyms();
        synsInNonSelectClauses.insert(synonyms.begin(), synonyms.end());

        PatternClausePtr pcPtr;
        pcPtr = patternClause.getSharedPtr();
        allClauses.push_back(pcPtr);
    }

    for (WithClause withClause : withClauses) {
        list<string> synonyms = withClause.getSynonyms();
        synsInNonSelectClauses.insert(synonyms.begin(), synonyms.end());

        WithClausePtr wcPtr;
        wcPtr = withClause.getSharedPtr();
        allClauses.push_back(wcPtr);
    }

    /*
        Create a smaller version of SelectClause that only contains the
        synonyms that are not in the other clauses (if applicable)
    */
    unordered_set<string> absentSynsInNonSelectClause;
    list<string> selectedSyns = selectClause.getSynonyms();
    for (string syn : selectedSyns) {
        if (synsInNonSelectClauses.find(syn) == synsInNonSelectClauses.end())
            absentSynsInNonSelectClause.insert(syn);
    }

    if (absentSynsInNonSelectClause.size() > 0) {
        // If there are synonyms in the select clause that are absent in the non-select clauses,
        // create a "modified select clause" to evaluate the said synonyms.
        SelectionType selectionType = selectClause.getSelectionType();

        SelectClausePtr scPtr;
        if (selectionType == SelectionType::SELECT_SINGLE) {
            Entity singleArgType = selectClause.getSingleArgType();
            string singleArg = selectClause.getSingleArg();
            scPtr = SelectClausePtr(new SelectClause(selectionType, singleArgType, singleArg));
        } else {
            assert(selectionType == SelectionType::SELECT_TUPLE);
            vector<Entity> tupleArgTypes = selectClause.getTupleArgTypes();
            vector<string> tupleArgs = selectClause.getTupleArgs();
            scPtr = SelectClausePtr(new SelectClause(selectionType, tupleArgTypes, tupleArgs));
        }
        allClauses.push_back(scPtr);
    }

    return allClauses;
}

/*
    Based on the information extracted from the "query tree", this method groups
    the clauses based on common synonyms and store them in the _clauseGroups private
    attribute.

    Note: This method does not sort the clauses within the clause group.
*/
void Optimizer::formClauseGroups()
{
    SynonymUFDS synUfds;

    vector<ClausePtr> clausesWithoutSynonym;

    // Group synonyms
    for (ClausePtr clause : _clauseVector) {
        list<string> synonyms = clause->getSynonyms();

        if (synonyms.size() == 0) {
            clausesWithoutSynonym.push_back(clause);
        } else {

            // Add the first synonym
            int syn1Idx = _synToIdxMap.at(synonyms.front());
            synonyms.pop_front();
            if (!synUfds.synonymPresent(syn1Idx))
                synUfds.addSynonym(syn1Idx);

            // Need to remember last synonym for union purposes
            int prevSynonym = syn1Idx;
            int currSynonym;
            while (!synonyms.empty()) {
                currSynonym = _synToIdxMap.at(synonyms.front());
                synonyms.pop_front();

                if (!synUfds.synonymPresent(currSynonym))
                    synUfds.addSynonym(currSynonym);

                synUfds.unionSet(prevSynonym, currSynonym);
                prevSynonym = currSynonym;
            }
        }
    }

    list<list<int>> synGroups = synUfds.getSynonymGroups();

    // Get clause groups from synonym groups
    if (!clausesWithoutSynonym.empty()) {
        _clauseGroupsVec.push_back(clausesWithoutSynonym);     // Clause group without synonym queue first
    }

    for (list<int> synGroup : synGroups) {

        unordered_set<int> clauseGroupUnique;
        vector<ClausePtr> clauseGroupVec;

        for (int synIdx : synGroup) {
            list<int> relevantClausesIdxs = _synIdxToClauseIdxsMap[synIdx];
            for (int relevantClauseIdx : relevantClausesIdxs) {
                clauseGroupUnique.insert(relevantClauseIdx);
            }
        }

        // Get actual clause from clause index and add to clause group
        for (int relevantClauseIdx : clauseGroupUnique) {
            ClausePtr clauseWrapper = _clauseVector[relevantClauseIdx];
            clauseGroupVec.push_back(clauseWrapper);
        }

        ClauseGroup clauseGroup = ClauseGroup(clauseGroupVec);
        clauseGroup.setSelectedSynonyms(_selectedSynonyms);
        _clauseGroupsVec.push_back(clauseGroup);
    }
}

void Optimizer::sortClauseGroups()
{
    sort(_clauseGroupsVec.begin(), _clauseGroupsVec.end(), Optimizer::compareClauseGroupCost);
}

/*
    Use queues to enforces FIFO policy of evaluating sorted clause groups
    and clauses within clause groups.
*/
queue<ClauseGroup> Optimizer::createClauseGroupQueue()
{
    queue<ClauseGroup> clauseGroupsQueue;

    for (ClauseGroup clauseGroup : _clauseGroupsVec) {
        clauseGroupsQueue.push(clauseGroup);
    }
    return clauseGroupsQueue;
}

bool Optimizer::compareClauseGroupCost(ClauseGroup clauseGroup1, ClauseGroup clauseGroup2)
{
    return clauseGroup1.getCost() < clauseGroup2.getCost();
}
