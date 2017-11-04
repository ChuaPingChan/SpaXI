#pragma once

#include <vector>

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
    void sortClauses();
    vector<ClausePtr> getClauseGroup();

    /* Used for sorting clauses in clause group */
    static bool compareClauseCost(ClausePtr clausePtr1, ClausePtr clausePtr2);

private:
    vector<ClausePtr> _clauseGroup;
    int _cost;

    int computeCost();

};

