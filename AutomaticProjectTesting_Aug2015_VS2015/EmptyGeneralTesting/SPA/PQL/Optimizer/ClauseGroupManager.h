#pragma once

#include <queue>
#include <unordered_set>
#include "../Utilities/ClauseWrapper.h"
#include "../Utilities/ClauseResult.h"

using namespace std;

class ClauseGroupManager
{
public:
    ClauseGroupManager();

    /*
        TODO:
        - API for evaluator to get ClauseGroup
        - API for evaluator to add computed results for each clausegroup
    */
    queue<ClauseWrapper> getNextClauseGroup();
    void processClauseResult(ClauseResult clauseResult);     // TODO: Rename this to ClauseGroupResult nearing submission
    void setSelectedSynonyms(list<string> synonyms);
    void setClauseGroupQueue(queue<queue<ClauseWrapper>> &clauseGroupQueue);
    ClauseResult getMergedClauseResult();

protected:
    unordered_set<string> _selectedSynonyms;
    queue<queue<ClauseWrapper>> _clauseGroupQueue;
    ClauseResult _mergedClauseResult;

    bool synonymIsSelected(string synName);

};

