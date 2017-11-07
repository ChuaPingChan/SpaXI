#include "ClauseGroupManager.h"
#include "../Utilities/ClauseResult.h"

ClauseGroupManager::ClauseGroupManager()
{
}

bool ClauseGroupManager::hasNextClauseGroup()
{
    return !(_clauseGroupQueue.empty());
}

ClauseGroup ClauseGroupManager::getNextClauseGroup()
{
    ClauseGroup nextClauseGroup = _clauseGroupQueue.front();
    _clauseGroupQueue.pop();
    return nextClauseGroup;
}

/*
    Merges the newly computed results of a new clause group into _mergedClauseResult
*/
void ClauseGroupManager::mergeClauseResult(ClauseResult clauseResult)
{
    _mergedClauseResult.mergeClauseResult(clauseResult, _selectedSynonyms);
}

void ClauseGroupManager::setSelectedSynonyms(list<string> synonyms)
{
    for (string synName : synonyms)
        _selectedSynonyms.insert(synName);
}

void ClauseGroupManager::setClauseGroupQueue(queue<ClauseGroup>& clauseGroupQueue)
{
    _clauseGroupQueue = clauseGroupQueue;
}

ClauseResult ClauseGroupManager::getMergedClauseResult()
{
    return _mergedClauseResult;
}

unordered_set<string> ClauseGroupManager::getSelectedSynonyms()
{
    return _selectedSynonyms;
}
