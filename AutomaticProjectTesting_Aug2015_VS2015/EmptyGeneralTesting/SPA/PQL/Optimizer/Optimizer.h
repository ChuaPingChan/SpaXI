#pragma once

#include "../QueryTree.h"
#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseWrapper.h"

using namespace std;

class Optimizer
{
public:
    Optimizer(QueryTree &queryTree);

protected:

    vector<string> _synVector;    // Index to synonym map
    unordered_map<string, int> _synToIdxMap;    // Synonym to index map
    vector<ClauseWrapper> _clauseVector;     // Index to clause map
    unordered_map<int, list<int>> _synIdxToClauseIdxsMap;   // Synonym to clause index map

    ClauseGroupsManager _clauseGroupsManager;
    
    // Vector is chosen to swap elements easily. To be converted to queues before passing to evaluator.
    vector<vector<ClauseWrapper>> _clauseGroups;
    
    bool processQueryTree(QueryTree &queryTree);
    list<ClauseWrapper> extractClausesFromQueryTree(QueryTree &queryTree);    // TODO: Rename if QueryTree's name changes
    void formClauseGroups();
    void sortClausesWithinGroup();
    void sortClauseGroups();
    queue<queue<ClauseWrapper>> createClauseGroupQueue();

};
