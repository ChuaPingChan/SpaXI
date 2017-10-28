#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseResult.h"

ClauseGroupsManager::ClauseGroupsManager()
{
}

queue<ClauseWrapper> ClauseGroupsManager::getNextClauseGroup()
{
    queue<ClauseWrapper> nextClauseGroup = _clauseGroupQueue.front();
    _clauseGroupQueue.pop();
    return nextClauseGroup;
}

/*
    Merges the newly computed results of a new clause group into _mergedClauseResult
*/
void ClauseGroupsManager::processClauseResult(ClauseResult clauseResult)
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

void ClauseGroupsManager::setSelectedSynonyms(list<string> synonyms)
{
    for (string synName : synonyms)
        _selectedSynonyms.insert(synName);
}

void ClauseGroupsManager::setClauseGroupQueue(queue<queue<ClauseWrapper>>& clauseGroupQueue)
{
    _clauseGroupQueue = clauseGroupQueue;
}

ClauseResult ClauseGroupsManager::getMergedClauseResult()
{
    return _mergedClauseResult;
}

bool ClauseGroupsManager::synonymIsSelected(string synName)
{
    return _selectedSynonyms.find(synName) != _selectedSynonyms.end();
}
