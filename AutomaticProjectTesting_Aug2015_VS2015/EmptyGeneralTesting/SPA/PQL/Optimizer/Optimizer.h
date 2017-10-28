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
    unordered_map<string, list<int>> _synToClauseIdxsMap;   // Synonym to clause index map

    ClauseGroupsManager _clauseGroupsManager;
    vector<vector<ClauseWrapper>> _clauseGroups;     // To be manipulated and given to ClauseGroupManager
    
    bool processQueryTree(QueryTree &queryTree);
    list<ClauseWrapper> extractClausesFromQueryTree(QueryTree &queryTree);    // TODO: Rename if QueryTree's name changes
    void formClauseGroups();

};
