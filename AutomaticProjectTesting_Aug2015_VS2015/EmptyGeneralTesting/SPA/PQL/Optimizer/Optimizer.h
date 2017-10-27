#pragma once

#include "../QueryTree.h"
#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseWrapper.h"

using namespace std;

class Optimizer
{
public:
    Optimizer(const QueryTree &queryTree);

protected:

    vector<string> _synVector;    // Index to synonym map
    unordered_map<string, int> _synToIdxMap;    // Synonym to index map
    vector<string> _clauseVector;     // Index to clause map

    ClauseGroupsManager clauseGroupsManager;
    vector<vector<ClauseWrapper>> clauseGroups;     // To be manipulated and given to ClauseGroupManager
    
    bool processQueryTree(const QueryTree &queryTree);

};
