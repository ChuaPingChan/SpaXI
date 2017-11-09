#include "ParentToChildStarTable.h"

using namespace std;

ParentToChildStarTable::ParentToChildStarTable()
{
}

/*
This method adds the parent child relationship
*/
bool ParentToChildStarTable::addParentChild(int parentStmt, int childStmt)
{
	parentToChildStarMap[parentStmt].push_back(childStmt);
	parentToChildStarRelMap[parentStmt].insert(childStmt);
	return true;
}

list<int> ParentToChildStarTable::getChildren(int parentStmt) {
	if (parentToChildStarMap.find(parentStmt) == parentToChildStarMap.end()) {
		return list<int>();
	}
	return parentToChildStarMap[parentStmt];
}

/*
This method iterates through the new map and popualte the correct information
*/
void ParentToChildStarTable::setMap(unordered_map<int, list<int>> target) {
	int key;
	list<int> valueList;
	for (auto it : target) {
		key = it.first;
		valueList = it.second;
		for (int value : valueList) {
			parentList.push_back(key);
			childList.push_back(value);
			parentToChildStarRelMap[key].insert(value);
		}
	}

	parentToChildStarPair = make_pair(parentList, childList);
	parentList.sort();
	parentList.unique();
	childList.sort();
	childList.unique();
	parentToChildStarMap = target;
}

bool ParentToChildStarTable::isParentStarChild(int parentStmt, int childStmt) {
	if (parentToChildStarRelMap.find(parentStmt) != parentToChildStarRelMap.end()) {
		return parentToChildStarRelMap[parentStmt].find(childStmt) != parentToChildStarRelMap[parentStmt].end();
	}
	return false;
}

pair<list<int>, list<int>> ParentToChildStarTable::getAllParentStarRel() {
	return parentToChildStarPair;
}