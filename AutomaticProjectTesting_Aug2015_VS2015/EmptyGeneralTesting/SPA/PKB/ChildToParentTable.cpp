#include "ChildToParentTable.h"

using namespace std;

ChildToParentTable::ChildToParentTable()
{
}

bool ChildToParentTable::addChildParent(int childStmt, int parentStmt)
{
	//If parent doesnt exist in map, create new parent
	if (childToParentMap.find(childStmt) == childToParentMap.end()) {
		childToParentMap[childStmt] = parentStmt;
		return true;
	}

	// by any change it was already initialised
	else {
		childToParentMap[childStmt] = parentStmt;
	}

	return false;
}

int ChildToParentTable::getParent(int childStmt) {
	return childToParentMap[childStmt];
}

unordered_map<int, list<int>> ChildToParentTable::getTable() {
	return childToParentMap;
}