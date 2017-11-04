#include "ClauseGroup.h"
#include "ClauseCostCalculator.h"

ClauseGroup::ClauseGroup(vector<ClausePtr> clauseGroup)
{
    _clauseGroup = clauseGroup;
    _cost = computeCost();
}

int ClauseGroup::getCost()
{
    return _cost;
}

vector<ClausePtr> ClauseGroup::getClauseGroup()
{
    return _clauseGroup;
}

int ClauseGroup::computeCost()
{
    int totalCost = 0;

    for (ClausePtr clausePtr : _clauseGroup) {
        // TODO: Implement
    }
}
