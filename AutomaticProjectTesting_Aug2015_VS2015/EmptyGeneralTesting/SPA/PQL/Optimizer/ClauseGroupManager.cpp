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
void ClauseGroupManager::processClauseResult(ClauseResult clauseResult)
{
    // Get all selected synonyms in clause result
    list<string> synsInClauseResult = clauseResult.getAllSynonyms();
    list<string> selectedSyns;
    for (string synName : synsInClauseResult) {
        if (synonymIsSelected(synName))
            selectedSyns.push_back(synName);
    }
    list<list<int>> resultsToMerge = clauseResult.getSynonymResults(selectedSyns);

    _mergedClauseResult.updateSynResults(selectedSyns, resultsToMerge);
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

bool ClauseGroupManager::synonymIsSelected(string synName)
{
    return _selectedSynonyms.find(synName) != _selectedSynonyms.end();
}
