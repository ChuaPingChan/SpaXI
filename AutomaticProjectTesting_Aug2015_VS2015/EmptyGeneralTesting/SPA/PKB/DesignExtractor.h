#pragma once
#include <unordered_map>
#include <list>
#include <ParentToChildTable.h>
#include <ParentToChildStarTable.h>
#include <ChildToParentTable.h>

using namespace std;

class DesignExtractor {
	public:
		DesignExtractor();
		unordered_map<int, list<int>> computeParentToChildStarTable(ParentToChildTable);
		unordered_map<int, list<int>> computeChildToParentStarTable(ChildToParentTable);
};