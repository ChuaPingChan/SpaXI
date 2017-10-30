#pragma once

#include <queue>
#include <unordered_set>
#include "../Utilities/Clause.h"
#include "../Utilities/ClauseResult.h"

using namespace std;

/*
    Manages clause groups and the results of clause groups.
*/
class ClauseGroupManager
{
public:
    ClauseGroupManager();

    // API for evaluator
    queue<Clause> getNextClauseGroup();
    void mergeClauseResult(ClauseResult clauseResult);     // TODO: Rename this to ClauseGroupResult nearing submission

    // API for optimizer
    void setSelectedSynonyms(list<string> synonyms);
    void setClauseGroupQueue(queue<queue<Clause>> &clauseGroupQueue);

    // API for result formatter
    ClauseResult getMergedClauseResult();

protected:
    unordered_set<string> _selectedSynonyms;
    queue<queue<Clause>> _clauseGroupQueue;
    ClauseResult _mergedClauseResult;

};

