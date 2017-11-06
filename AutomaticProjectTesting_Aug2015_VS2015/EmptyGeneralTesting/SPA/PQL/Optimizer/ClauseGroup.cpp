#include <algorithm>

#include "ClauseGroup.h"
#include "ClauseCostCalculator.h"

using namespace std;

ClauseGroup::ClauseGroup(vector<ClausePtr> clauseGroup)
{
    _initClauseVec = clauseGroup;
    sortInitClauseVec();

    for (ClausePtr clausePtr : clauseGroup) {
        _clauseQueue.push(clausePtr);
    }

    _cost = computeCost();
}

int ClauseGroup::getCost()
{
    return _cost;
}

bool ClauseGroup::hasNextClause()
{
    return !(_clauseQueue.empty());
}

ClausePtr& ClauseGroup::front()
{
    return _clauseQueue.front();
}

void ClauseGroup::pop()
{
    _clauseQueue.pop();
}

int ClauseGroup::size()
{
    return _clauseQueue.size();
}

void ClauseGroup::sortInitClauseVec()
{
    sort(_initClauseVec.begin(), _initClauseVec.end(), ClauseGroup::compareClauseCost);
}

//vector<ClausePtr> ClauseGroup::getClauseGroup()
//{
//    return _initClauseVec;
//}

int ClauseGroup::computeCost()
{
    int totalCost = 0;

    for (ClausePtr clausePtr : _initClauseVec) {
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
