#pragma once

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

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

    bool pruneClauseResult(ClauseResult crToPrune);

    /* Used for sorting clauses in clause group */
    static bool compareClauseCost(ClausePtr clausePtr1, ClausePtr clausePtr2);

private:

    unordered_set<string> _selectedSynonyms;

    void sortInitClauseVec();
    vector<ClausePtr> _initClauseVec;
    queue<ClausePtr> _clauseQueue;
    int _cost;

    // For pruning
    unordered_set<string> _synsInRemainingClauses;
    unordered_map<string, int> _remainingSynsCount;

    int computeCost();
};
