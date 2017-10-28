#include "Optimizer.h"
#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseWrapper.h"

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
                _synToClauseIdxsMap[synonym].push_back(clauseIdx);
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

void Optimizer::formClauseGroups()
{
    // TODO: Implement
}
