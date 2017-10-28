#include <cassert>
#include "Optimizer.h"
#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseWrapper.h"
#include "SynonymUFDS.h"

Optimizer::Optimizer(QueryTree &queryTree)
{
    // TODO: Implement
    /*
        1. Populates and initialises internal data structures
        2. Split clauses into groups
        3. Sort clauses within groups for efficient evaluation
        4. Sort clause groups for efficient evaluation
    */
    processQueryTree(queryTree);
    formClauseGroups();
    sortClausesWithinGroup();
    sortClauseGroups();
    _clauseGroupsManager = ClauseGroupsManager(createClauseGroupQueue())      // TODO: Implement
}

/*
    Loops through all clauses in a query tree and updates the appropriate data
    structures in Optimizer.
*/
bool Optimizer::processQueryTree(QueryTree &queryTree)
{

    // TODO: Implement
    list<ClauseWrapper> allClauses = extractClausesFromQueryTree(queryTree);

    for (ClauseWrapper clause : allClauses) {

        // TODO: Optimisation idea - ignore duplicate clauses, or remove them earlier
        _clauseVector.push_back(clause);
        int clauseIdx = _clauseVector.size() - 1;   // Clause just added should be the last element

        // Assign index to each new synonyms
        list<string> synonyms = clause.getClause().getSynonyms();
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
    Extracts all clauses in a given query.
*/
list<ClauseWrapper> Optimizer::extractClausesFromQueryTree(QueryTree &queryTree)
{
    list<ClauseWrapper> allClauses;

    vector<SuchThatClause> suchThatClauses = queryTree.getSuchThatClauses();
    vector<PatternClause> patternClauses = queryTree.getPatternClauses();
    vector<WithClause> withClauses = queryTree.getWithClauses();

    for (SuchThatClause suchThatClause : suchThatClauses) {
        ClauseWrapper clause(suchThatClause);
        allClauses.push_back(clause);
    }

    for (PatternClause patternClause : patternClauses) {
        ClauseWrapper clause(patternClause);
        allClauses.push_back(clause);
    }

    for (WithClause withClause : withClauses) {
        ClauseWrapper clause(withClause);
        allClauses.push_back(clause);
    }

    return allClauses;
}

/*
    Based on the information extracted from the "query tree", this method groups
    the clauses based on common synonyms and store them in the _clauseGroups private
    attribute.
*/
void Optimizer::formClauseGroups()
{
    SynonymUFDS synUfds;

    vector<ClauseWrapper> clausesWithoutSynonym;

    // Group synonyms
    for (ClauseWrapper clauseWrapper : _clauseVector) {
        Clause clause = clauseWrapper.getClause();
        list<string> synonyms = clause.getSynonyms();

        if (synonyms.size() == 0) {
            clausesWithoutSynonym.push_back(clauseWrapper);
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
    _clauseGroups.push_back(clausesWithoutSynonym);
    for (list<int> synGroup : synGroups) {

        unordered_set<int> clauseGroupUnique;
        vector<ClauseWrapper> clauseGroup;

        for (int synIdx : synGroup) {
            list<int> relevantClausesIdxs = _synIdxToClauseIdxsMap[synIdx];
            for (int relevantClauseIdx : relevantClausesIdxs) {
                clauseGroupUnique.insert(relevantClauseIdx);
            }
            for (int relevantClauseIdx : clauseGroupUnique) {
                ClauseWrapper clauseWrapper = _clauseVector[relevantClauseIdx];
                clauseGroup.push_back(clauseWrapper);
            }
        }

        _clauseGroups.push_back(clauseGroup);

    }
}

void Optimizer::sortClausesWithinGroup()
{
    // TODO: Implement
}

void Optimizer::sortClauseGroups()
{
    // TODO: Implement
}

/*
    Enforces FIFO policy of evaluating sorted clause groups and clauses in 
    groups using queues.
*/
queue<queue<ClauseWrapper>> Optimizer::createClauseGroupQueue()
{
    queue<queue<ClauseWrapper>> clauseGroupsQueue;

    for (vector<ClauseWrapper> clauseGroup : _clauseGroups) {
        queue<ClauseWrapper> clauseQueue;
        for (ClauseWrapper clause : clauseGroup) {
            clauseQueue.push(clause);
        }
        clauseGroupsQueue.push(clauseQueue);
    }
    return clauseGroupsQueue;
}
