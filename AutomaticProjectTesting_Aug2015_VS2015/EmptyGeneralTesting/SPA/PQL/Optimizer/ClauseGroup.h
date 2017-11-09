#pragma once

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "../Utilities/Clause.h"
#include "../Utilities/ClauseResult.h"

using namespace std;

/*
    Represents a clause group, storing a backing vector for the actual
    clause group, along with other meta-information like the computational
    cost of the clause group.
*/
class ClauseGroup
{
public:
    ClauseGroup(vector<ClausePtr> clauseGroup);

    bool setSelectedSynonyms(unordered_set<string> selectedSyns);   // TODO: Embed this in constructor
    int getCost();
    bool hasNextClause();
    ClausePtr& getNextClause();
    int size();

    bool pruneClauseResult(ClauseResult* crToPrune);

    /* Used for sorting clauses in clause group */
    static bool compareClauseCost(pair<ClausePtr, int> c1, pair<ClausePtr, int> c2);

private:

    unordered_set<string> _selectedSynonyms;

    void sortClauseVec();
    vector<pair<ClausePtr, int>> _initClauseVec;   // Permanently stores all the clauses used to construct this ClauseGroup
    queue<pair<ClausePtr, int>> _clauseQueue;   // Dynamic queue of clauses
    int _cost;

    // For pruning
    unordered_set<string> _synsInRemainingClauses;
    unordered_map<string, int> _remainingSynsCount;

    int computeCost();
    void relaxRemainingClauseCost(vector<pair<ClausePtr, int>>::iterator nextIter, unordered_set<string> evaluatedSyns);
};
