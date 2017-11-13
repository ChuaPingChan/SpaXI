#pragma once
#include <unordered_map>
#include <list>
#include "ParentToChildTable.h"
#include "ChildToParentTable.h"
#include "ChildToParentStarTable.h"
#include "FollowsTable.h"
#include "CallsTable.h"
#include "UsesTableProcToVar.h"
#include "UsesTableStmtToVar.h"
#include "StmtTypeList.h"
#include "ModTableProcToVar.h"
#include "ModTableStmtToVar.h"
#include "CallsStarTable.h"
#include <queue>
#include <unordered_set>

using namespace std;

class DesignExtractor {
public:
    DesignExtractor();
    unordered_map<int, list<int>> computeTransitiveClosure(unordered_map<int, list<int>> initialMap);
    unordered_map<int, list<int>> computeTransitiveClosure(unordered_map<int, int> initialMap);
    unordered_map<int, list<int>> computeParentToChildStarTable(ParentToChildTable);
    unordered_map<int, list<int>> computeChildToParentStarTable(ChildToParentTable);
    unordered_map<int, list<int>> computeFollowsStarAfterTable(FollowsTable followsTable);
    unordered_map<int, list<int>> computeFollowsStarBeforeTable(FollowsTable followsTable);
    pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>> computeCallsStarTable(CallsTable callsTable);
    unordered_map<int, list<int>> computeUsesTable(UsesTableProcToVar usesTable, CallsStarTable callsStarTable);
    void DFS(int curr, unordered_map<int, list<int>> &map, unordered_set<int> &visited, unordered_map<int, list<int>> &callsStarMap);
    unordered_map<int, list<int>> computeModifiesTable(ModTableProcToVar modTable, CallsStarTable callsStarTable);
    unordered_map<int, list<int>> computeUsesTable(UsesTableStmtToVar usesTableStmtToVar,
        StmtTypeList stmtTypeList, UsesTableProcToVar usesTableProcToVar, ChildToParentStarTable childToParentStarTable);
    unordered_map<int, list<int>> computeModifiesTable(ModTableStmtToVar modTableStmtToVar,
        StmtTypeList stmtTypeList, ModTableProcToVar modTableProcToVar, ChildToParentStarTable childToParentStarTable);
    unordered_map<int, list<int>> computeUsesTableStmt(UsesTableStmtToVar usesTableStmtToVar);
    unordered_map<int, list<int>> computeUsesTableProc(UsesTableProcToVar usesTableProcToVar);
    unordered_map<int, list<int>> computeModTableStmt(ModTableStmtToVar modTableStmtToVar);
    unordered_map<int, list<int>> computeModTableProc(ModTableProcToVar modTableProcToVar);
};