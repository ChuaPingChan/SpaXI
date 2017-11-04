#include <algorithm>

#include "ClauseGroup.h"
#include "ClauseCostCalculator.h"

using namespace std;

ClauseGroup::ClauseGroup(vector<ClausePtr> clauseGroup)
{
    _clauseGroup = clauseGroup;
    _cost = computeCost();
}

int ClauseGroup::getCost()
{
    return _cost;
}

void ClauseGroup::sortClauses()
{
    sort(_clauseGroup.begin(), _clauseGroup.end(), ClauseGroup::compareClauseCost);
}

vector<ClausePtr> ClauseGroup::getClauseGroup()
{
    return _clauseGroup;
}

int ClauseGroup::computeCost()
{
    int totalCost = 0;

    for (ClausePtr clausePtr : _clauseGroup) {
        totalCost += ClauseCostCalculator::getCost(clausePtr);
    }
    return totalCost;
}

/*
    Returns true if the first clause should be ordered before the second clause
*/
bool ClauseGroup::compareClauseCost(ClausePtr clausePtr1, ClausePtr clausePtr2)
{
    return ClauseCostCalculator::getCost(clausePtr1) < ClauseCostCalculator::getCost(clausePtr2);
}
