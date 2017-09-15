#include "ChildToParentStarTable.h"

using namespace std;

ChildToParentStarTable::ChildToParentStarTable()
{
}

list<int> ChildToParentStarTable::getParentStar(int childStmt) {
	return childToParentStarMap[childStmt];
}

void ChildToParentStarTable::setMap(unordered_map<int, list<int>> target) {
	childToParentStarMap = target;
}

bool ChildToParentStarTable::isParentStar(int parentStmt, int childStmt) {
	if (childToParentStarMap.find(childStmt) != childToParentStarMap.end()) {
		unordered_map<int, list<int>>::iterator it;
		it = childToParentStarMap.find(childStmt);
		if (std::find(it->second.begin(), it->second.end(), parentStmt) != it->second.end()) {
			return true;
		}
	}

	return false;
}