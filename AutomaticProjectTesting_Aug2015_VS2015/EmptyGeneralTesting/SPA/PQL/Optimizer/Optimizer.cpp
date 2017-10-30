#include <cassert>
#include "Optimizer.h"
#include "ClauseGroupManager.h"
#include "../Utilities/Clause.h"
#include "SynonymUFDS.h"

Optimizer::Optimizer(QueryTree &queryTree)
{
    // TODO: Implement
    /*
        Process description:
        1. Populates and initialises internal data structures
        2. Split clauses into groups
        3. Sort clauses within groups for efficient evaluation
        4. Sort clause groups for efficient evaluation
    */
    processQueryTree(queryTree);
    formClauseGroups();
    sortClausesWithinGroup();
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

    list<Clause> allClauses = extractClausesFromQueryTree(queryTree);

    for (Clause clause : allClauses) {

        // TODO: Optimisation idea - ignore duplicate clauses, or remove them earlier
        _clauseVector.push_back(clause);
        int clauseIdx = _clauseVector.size() - 1;   // Clause just added should be the last element

        // Assign index to each new synonyms
        list<string> synonyms = clause.getSynonyms();
        for (string synonym : synonyms) {
            if (_synToIdxMap.find(synonym) == _synToIdxMap.end()) {
                _synVector.push_back(synonym);
                int synIdx = _synVector.size() - 1;     // Synonym just added should be the last element
                _synToIdxMap[synonym] = synIdx;
                _synIdxToClauseIdxsMap[synIdx].push_back(clauseIdx);
            }
        }
    }

    return true;
}

/*
    Extracts all non-"select" clauses in a given query.
*/
list<Clause> Optimizer::extractClausesFromQueryTree(QueryTree &queryTree)
{
    list<Clause> allClauses;

    vector<SuchThatClause> suchThatClauses = queryTree.getSuchThatClauses();
    vector<PatternClause> patternClauses = queryTree.getPatternClauses();
    vector<WithClause> withClauses = queryTree.getWithClauses();

    for (SuchThatClause suchThatClause : suchThatClauses) {
        allClauses.push_back(suchThatClause);
    }

    for (PatternClause patternClause : patternClauses) {
        allClauses.push_back(patternClause);
    }

    for (WithClause withClause : withClauses) {
        allClauses.push_back(withClause);
    }

    return allClauses;
}

/*
    Based on the information extracted from the "query tree", this method groups
    the clauses based on common synonyms and store them in the _clauseGroups private
    attribute. Note that the "select" clause is not included because it doesn't need
    to be "evaluated".
*/
void Optimizer::formClauseGroups()
{
    // TODO before submission: Consider refactoring into helper methods to achieve SLA
    SynonymUFDS synUfds;

    vector<Clause> clausesWithoutSynonym;

    // Group synonyms
    for (Clause clause : _clauseVector) {
        list<string> synonyms = clause.getSynonyms();

        if (synonyms.size() == 0) {
            clausesWithoutSynonym.push_back(clause);
        } else if (synonyms.size() == 1) {
            int syn1Idx = _synToIdxMap.at(synonyms.front());
            if (!synUfds.synonymPresent(syn1Idx))
                synUfds.addSynonym(syn1Idx);
        } else {
            assert(synonyms.size() == 2);

            int syn1Idx = _synToIdxMap.at(synonyms.front());
            synonyms.pop_front();
            int syn2Idx = _synToIdxMap.at(synonyms.front());

            if (!synUfds.synonymPresent(syn1Idx))
                synUfds.addSynonym(syn1Idx);
            if (!synUfds.synonymPresent(syn2Idx))
                synUfds.addSynonym(syn2Idx);

            synUfds.unionSet(syn1Idx, syn2Idx);
        }
    }

    list<list<int>> synGroups = synUfds.getSynonymGroups();

    // Get clause groups from synonym groups
    _clauseGroups.push_back(clausesWithoutSynonym);     // Clause group without synonym queue first
    for (list<int> synGroup : synGroups) {

        unordered_set<int> clauseGroupUnique;
        vector<Clause> clauseGroup;

        for (int synIdx : synGroup) {
            list<int> relevantClausesIdxs = _synIdxToClauseIdxsMap[synIdx];
            for (int relevantClauseIdx : relevantClausesIdxs) {
                clauseGroupUnique.insert(relevantClauseIdx);
            }
            // Get actual clause from clause index and add to clause group
            for (int relevantClauseIdx : clauseGroupUnique) {
                Clause clauseWrapper = _clauseVector[relevantClauseIdx];
                clauseGroup.push_back(clauseWrapper);
            }
        }
        _clauseGroups.push_back(clauseGroup);
    }
}

void Optimizer::sortClausesWithinGroup()
{
    // TODO: Implement after integration is done
}

void Optimizer::sortClauseGroups()
{
    // TODO: Implement after integration is done
}

/*
    Enforces FIFO policy of evaluating sorted clause groups and clauses in
    groups using queues.
*/
queue<queue<Clause>> Optimizer::createClauseGroupQueue()
{
    queue<queue<Clause>> clauseGroupsQueue;

    for (vector<Clause> clauseGroup : _clauseGroups) {
        queue<Clause> clauseQueue;
        for (Clause clause : clauseGroup) {
            clauseQueue.push(clause);
        }
        clauseGroupsQueue.push(clauseQueue);
    }
    return clauseGroupsQueue;
}
