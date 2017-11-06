#pragma once

#include <queue>
#include <unordered_set>
#include "../Utilities/Clause.h"
#include "../Utilities/ClauseResult.h"
#include "ClauseGroup.h"

using namespace std;

/*
    Manages clause groups and the results of clause groups.
*/
class ClauseGroupManager
{
public:
    ClauseGroupManager();   // TODO: Disallow default constructor. Set clauseGroupQueue upon construction

    // API for evaluator
    bool hasNextClauseGroup();
    ClauseGroup getNextClauseGroup();
    void mergeClauseResult(ClauseResult clauseResult);     // TODO: Rename this to ClauseGroupResult nearing submission

    // API for optimizer
    void setSelectedSynonyms(list<string> synonyms);
    void setClauseGroupQueue(queue<ClauseGroup> &clauseGroupQueue);

    // API for result formatter
    ClauseResult getMergedClauseResult();

    // Redundant Utility API
    unordered_set<string> getSelectedSynonyms();

protected:
    unordered_set<string> _selectedSynonyms;
    queue<ClauseGroup> _clauseGroupQueue;
    ClauseResult _mergedClauseResult;

};

