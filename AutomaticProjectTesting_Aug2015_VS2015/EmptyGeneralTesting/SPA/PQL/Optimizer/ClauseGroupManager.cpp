#include "ClauseGroupManager.h"
#include "../Utilities/ClauseResult.h"

ClauseGroupManager::ClauseGroupManager()
{
}

queue<ClauseWrapper> ClauseGroupManager::getNextClauseGroup()
{
    queue<ClauseWrapper> nextClauseGroup = _clauseGroupQueue.front();
    _clauseGroupQueue.pop();
    return nextClauseGroup;
}

/*
    Merges the newly computed results of a new clause group into _mergedClauseResult
*/
void ClauseGroupManager::mergeClauseResult(ClauseResult clauseResult)
{
    _mergedClauseResult.mergeClauseResult(_selectedSynonyms, clauseResult);
}

void ClauseGroupManager::setSelectedSynonyms(list<string> synonyms)
{
    for (string synName : synonyms)
        _selectedSynonyms.insert(synName);
}

void ClauseGroupManager::setClauseGroupQueue(queue<queue<ClauseWrapper>>& clauseGroupQueue)
{
    _clauseGroupQueue = clauseGroupQueue;
}

ClauseResult ClauseGroupManager::getMergedClauseResult()
{
    return _mergedClauseResult;
}
