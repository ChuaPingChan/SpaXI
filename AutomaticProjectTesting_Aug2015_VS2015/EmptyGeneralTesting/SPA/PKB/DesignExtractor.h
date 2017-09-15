#pragma once
#include <unordered_map>
#include <list>
#include "ParentToChildTable.h"
#include "ChildToParentTable.h"
#include "FollowsTable.h"
#include <queue>

using namespace std;

class DesignExtractor {
	public:
		DesignExtractor();
		unordered_map<int, list<int>> computeParentToChildStarTable(ParentToChildTable);
		unordered_map<int, list<int>> computeChildToParentStarTable(ChildToParentTable);
		unordered_map<int, list<int>> computeFollowsStarAfterTable(FollowsTable followsTable);
		unordered_map<int, list<int>> computeFollowsStarBeforeTable(FollowsTable followsTable);
};