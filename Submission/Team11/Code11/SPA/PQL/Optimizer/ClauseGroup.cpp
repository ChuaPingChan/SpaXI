#include <cassert>
#include <algorithm>

#include "../Utilities/ClauseResult.h"
#include "ClauseGroup.h"
#include "ClauseCostCalculator.h"

using namespace std;

ClauseGroup::ClauseGroup(vector<ClausePtr> clauseGroup)
{
    for (ClausePtr clausePtr : clauseGroup) {
        int clauseCost = ClauseCostCalculator::getCost(clausePtr);
        _initClauseVec.push_back(pair<ClausePtr, int>(clausePtr, clauseCost));
    }

    sortClauseVec();

    for (pair<ClausePtr,int> clausePtrCostPair : _initClauseVec) {

        ClausePtr clausePtr = clausePtrCostPair.first;

        // Data to facilitate pruning
        list<string> syns = clausePtr->getSynonyms();
        for (string syn : syns) {
            _remainingSynsCount[syn]++;
            _synsInRemainingClauses.insert(syn);
        }

        _clauseQueue.push(clausePtrCostPair);
    }

    _cost = computeCost();
}

bool ClauseGroup::setSelectedSynonyms(unordered_set<string> selectedSynonyms)
{
    _selectedSynonyms = selectedSynonyms;
    return true;
}

int ClauseGroup::getCost()
{
    return _cost;
}

bool ClauseGroup::hasNextClause()
{
    return !(_clauseQueue.empty());
}

ClausePtr& ClauseGroup::getNextClause()
{
    ClausePtr& clausePtr = _clauseQueue.front().first;
    _clauseQueue.pop();

    // Update DS for pruning
    list<string> syns = clausePtr->getSynonyms();
    for (string syn : syns) {
        assert(_remainingSynsCount.find(syn) != _remainingSynsCount.end());
        _remainingSynsCount[syn]--;
        if (_remainingSynsCount[syn] == 0) {
            _synsInRemainingClauses.erase(syn);
            // Note: There's no need to erase syn from _remainingSynCount. Avoid overhead.
        }
    }

    return clausePtr;
}

int ClauseGroup::size()
{
    return _clauseQueue.size();
}

/*
    Removes the columns of the intermediate results table which synonyms are
    not selected and are not present in the remaining un-evaluated clauses
    in the clause group.

    Pre-condition: The clause result must be corresponding to this clause group
*/
bool ClauseGroup::pruneClauseResult(ClauseResult* crToPrune)
{
    unordered_set<string> synsToRetain;
    synsToRetain.insert(_synsInRemainingClauses.begin(), _synsInRemainingClauses.end());
    synsToRetain.insert(_selectedSynonyms.begin(), _selectedSynonyms.end());

    return crToPrune->pruneColumns(synsToRetain);
}

void ClauseGroup::sortClauseVec()
{
    // Initial sorting of clauses with the cost calculated independent of other clauses
    sort(_initClauseVec.begin(), _initClauseVec.end(), ClauseGroup::compareClauseCost);

    // Next, if there are more than 2 clauses,
    // take into account the synonyms processed before a particular clause is processed
    // and sort again. This is an O(N^2 log N) operation, where N is the number of clauses.
    if (_initClauseVec.size() < 3)
        return;

    for (vector<pair<ClausePtr, int>>::iterator clausePtrCostPairIter = _initClauseVec.begin();
        clausePtrCostPairIter != _initClauseVec.end();  // Do this only up to the second-last clause
        clausePtrCostPairIter++)
    {
        list<string> syns = clausePtrCostPairIter->first->getSynonyms();
        if (syns.empty())
            continue;

        relaxRemainingClauseCost(clausePtrCostPairIter, unordered_set<string>(syns.begin(), syns.end()));
        
        if ((_initClauseVec.end() - clausePtrCostPairIter) >= 2) {  // Sort only if there are > 1 remaining clauses
            sort(clausePtrCostPairIter + 1, _initClauseVec.end(), ClauseGroup::compareClauseCost);
        }
    }
}

void ClauseGroup::relaxRemainingClauseCost(vector<pair<ClausePtr, int>>::iterator currIter,
    unordered_set<string> evaluatedSyns)
{
    currIter++;
    while (currIter != _initClauseVec.end()) {
        ClausePtr clausePtr = currIter->first;
        int updatedCost = ClauseCostCalculator::getRelaxedCost(clausePtr, evaluatedSyns);
        currIter->second = updatedCost;
        currIter++;
    }
}

int ClauseGroup::computeCost()
{
    int totalCost = 0;

    for (pair<ClausePtr,int> clausePtrCostPair : _initClauseVec) {
        totalCost += clausePtrCostPair.second;
    }
    return totalCost;
}

/*
    Returns true if the first clause should be ordered before the second clause
*/
bool ClauseGroup::compareClauseCost(pair<ClausePtr,int> c1, pair<ClausePtr,int> c2)
{
    return c1.second < c2.second;
}
