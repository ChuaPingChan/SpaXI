#pragma once

#include <queue>
#include <unordered_set>
#include "../Utilities/Clause.h"
#include "../Utilities/ClauseResult.h"

using namespace std;

class ClauseGroupManager
{
public:
    ClauseGroupManager();

    queue<Clause> getNextClauseGroup();
    void mergeClauseResult(ClauseResult clauseResult);     // TODO: Rename this to ClauseGroupResult nearing submission
    void setSelectedSynonyms(list<string> synonyms);
    void setClauseGroupQueue(queue<queue<Clause>> &clauseGroupQueue);
    ClauseResult getMergedClauseResult();

protected:
    unordered_set<string> _selectedSynonyms;
    queue<queue<Clause>> _clauseGroupQueue;
    ClauseResult _mergedClauseResult;

};

