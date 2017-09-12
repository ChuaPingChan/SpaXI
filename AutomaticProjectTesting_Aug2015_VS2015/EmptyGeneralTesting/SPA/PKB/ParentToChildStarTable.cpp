#include "ParentToChildStarTable.h"

using namespace std;

ParentToChildStarTable::ParentToChildStarTable()
{
}

bool ParentToChildStarTable::addParentChild(int parentStmt, int childStmt)
{
	//If parent doesnt exist in map, create new parent
	if (parentToChildStarMap.find(parentStmt) == parentToChildStarMap.end()) {
		parentToChildStarMap[parentStmt] = list<int>();
		parentToChildStarMap[parentStmt].push_back(childStmt);
		return true;
	}

	else {
		parentToChildStarMap[parentStmt].push_back(childStmt);
		parentToChildStarMap[parentStmt].unique();
		return true;
	}

	return false;
}

list<int> ParentToChildStarTable::getChildren(int parentStmt) {
	return parentToChildStarMap[parentStmt];
}