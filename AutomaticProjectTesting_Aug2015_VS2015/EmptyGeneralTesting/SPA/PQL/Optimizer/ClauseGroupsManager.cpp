#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseResult.h"

ClauseGroupsManager::ClauseGroupsManager(queue<queue<ClauseWrapper>> &clauseGroupsQueue)
{
    _clauseGroupQueue = clauseGroupsQueue;
}

queue<ClauseWrapper> ClauseGroupsManager::getNextClauseGroup()
{
    queue<ClauseWrapper> nextClauseGroup = _clauseGroupQueue.front();
    _clauseGroupQueue.pop();
    return nextClauseGroup;
}

void ClauseGroupsManager::processClauseResult(ClauseResult clauseResult)
{
    // TODO: Implement
}
