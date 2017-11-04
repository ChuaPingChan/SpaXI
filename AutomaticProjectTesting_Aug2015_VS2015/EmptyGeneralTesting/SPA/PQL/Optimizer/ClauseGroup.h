#pragma once

#include <vector>

#include "../Utilities/Clause.h"

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
    vector<ClausePtr> getClauseGroup();

private:
    vector<ClausePtr> _clauseGroup;
    int _cost;

    int computeCost();

};

