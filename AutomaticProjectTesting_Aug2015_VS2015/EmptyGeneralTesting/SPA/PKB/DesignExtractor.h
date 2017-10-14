#pragma once
#include <unordered_map>
#include <list>
#include "ParentToChildTable.h"
#include "ChildToParentTable.h"
#include "FollowsTable.h"
#include "CallsTable.h"
#include "UsesTableProcToVar.h"
#include "ModTableProcToVar.h"
#include "CallsStarTable.h"
#include <queue>
#include <unordered_set>

using namespace std;

class DesignExtractor {
	public:
		DesignExtractor();
		unordered_map<int, list<int>> computeParentToChildStarTable(ParentToChildTable);
		unordered_map<int, list<int>> computeChildToParentStarTable(ChildToParentTable);
		unordered_map<int, list<int>> computeFollowsStarAfterTable(FollowsTable followsTable);
		unordered_map<int, list<int>> computeFollowsStarBeforeTable(FollowsTable followsTable);
		pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>> computeCallsStarTable(CallsTable callsTable);
		unordered_map<int, pair<int, int>> computeFollowsTable(unordered_map<int, int> followsBefore, unordered_map<int, int> followsAfter);
		unordered_map<int, list<int>> computeUsesTable(UsesTableProcToVar usesTable, CallsStarTable callsStarTable);
		list<int> getPostfix(int root, unordered_map<int, list<int>> graph);
};