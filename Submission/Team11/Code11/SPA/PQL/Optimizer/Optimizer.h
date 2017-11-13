#pragma once

#include "../QueryTree.h"
#include "ClauseGroupManager.h"
#include "../Utilities/Clause.h"

using namespace std;

class Optimizer
{
public:
    Optimizer(QueryTree &queryTree);

    // API for evaluator
    ClauseGroupManager getClauseGroupManager();

protected:

    unordered_set<string> _selectedSynonyms;
    vector<string> _synVector;    // Index to synonym map
    unordered_map<string, int> _synToIdxMap;    // Synonym to index map
    vector<ClausePtr> _clauseVector;     // Index to clause map
    unordered_map<int, list<int>> _synIdxToClauseIdxsMap;   // Synonym to clause index map
    unordered_map<int, int> _clauseIdxToCostMap;   // Maps clause to their respective costs

    ClauseGroupManager _clauseGroupsManager;
    
    // Vector is chosen to swap elements easily. To be converted to queues before passing to evaluator.
    vector<ClauseGroup> _clauseGroupsVec;
    
    /******************
     * Helper Methods *
     ******************/
    bool processQueryTree(QueryTree &queryTree);
    bool extractSelectedSyns(QueryTree &queryTree);
    list<ClausePtr> extractClausesFromQueryTree(QueryTree &queryTree);    // TODO: Rename if QueryTree's name changes
    void formClauseGroups();
    void sortClauseGroups();
    queue<ClauseGroup> createClauseGroupQueue();
    static bool compareClauseGroupCost(ClauseGroup clauseGroup1, ClauseGroup clauseGroup2);

};
