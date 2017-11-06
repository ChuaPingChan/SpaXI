#pragma once

#include <vector>
#include <queue>

#include "../Utilities/Clause.h"

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

    int getCost();
    bool hasNextClause();
    ClausePtr& front();
    void pop();
    int size();
    //vector<ClausePtr> getClauseGroup();

    /* Used for sorting clauses in clause group */
    static bool compareClauseCost(ClausePtr clausePtr1, ClausePtr clausePtr2);

private:
    void sortInitClauseVec();
    vector<ClausePtr> _initClauseVec;
    queue<ClausePtr> _clauseQueue;
    int _cost;

    int computeCost();
};
