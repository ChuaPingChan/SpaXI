#include "ChildToParentTable.h"

using namespace std;

ChildToParentTable::ChildToParentTable()
{
}

bool ChildToParentTable::addChildParent(int childStmt, int parentStmt)
{
	if (parentStmt == 0) {
		return true;
	}

	//add to list of all children
	childList.push_back(childStmt);
	childList.sort();
	childList.unique();

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

bool ChildToParentTable::isChild(int childStmt) {
	if (childToParentMap.find(childStmt) != childToParentMap.end()) {
		return true;
	}

	return false;
}

int ChildToParentTable::getParent(int childStmt) {
	if (childToParentMap.find(childStmt) == childToParentMap.end()) {
		return 0;
	}

	return childToParentMap[childStmt];
}

unordered_map<int, int> ChildToParentTable::getTable() {
	return childToParentMap;
}

list<int> ChildToParentTable::getAllChildren() {
	list<int> stmtList;

	for (std::unordered_map<int, int>::iterator it = childToParentMap.begin(); it != childToParentMap.end(); ++it) {
		stmtList.push_back((*it).first);
	}

	return stmtList;
}