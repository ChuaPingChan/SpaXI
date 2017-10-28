#pragma once

#include <queue>
#include "../Utilities/ClauseWrapper.h"
#include "../Utilities/ClauseResult.h"

using namespace std;

class ClauseGroupsManager
{
public:
    ClauseGroupsManager(queue<queue<ClauseWrapper>> &clauseGroupsQueue);

    /*
        TODO:
        - API for evaluator to get ClauseGroup
        - API for evaluator to add computed results for each clausegroup
    */
    queue<ClauseWrapper> getNextClauseGroup();
    void processClauseResult(ClauseResult clauseResult);     // TODO: Rename this to ClauseGroupResult nearing submission

protected:
    queue<queue<ClauseWrapper>> _clauseGroupQueue;
    ClauseResult mergedClauseResult;

};

