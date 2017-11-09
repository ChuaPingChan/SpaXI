#include "ParentToChildTable.h"

using namespace std;

ParentToChildTable::ParentToChildTable()
{
}

/*
Populates the respective tables
*/
bool ParentToChildTable::addParentChild(int parentStmt, int childStmt) 
{
	if (parentStmt == 0) {
		return true;
	}

	parentToChildMap[parentStmt].push_back(childStmt);
	parentToChildRelMap[parentStmt].insert(childStmt);
	parentList.push_back(parentStmt);
	uniqueParentList.push_back(parentStmt);
	uniqueParentList.sort();
	uniqueParentList.unique();
	childList.push_back(childStmt);
	return true;
}

bool ParentToChildTable::isParent(int parentStmt) {
	if (parentToChildMap.find(parentStmt) != parentToChildMap.end()) {
		return true;
	}
	return false;
}

bool ParentToChildTable::empty() {
	return parentToChildMap.empty();
}

list<int> ParentToChildTable::getChildren(int parentStmt) {
	if (parentToChildMap.find(parentStmt) == parentToChildMap.end()) {
		return list<int>();
	}
	return parentToChildMap[parentStmt];
}

unordered_map<int, list<int>> ParentToChildTable::getTable() {
	return parentToChildMap;
}

bool ParentToChildTable::isParentChild(int parentStmt, int childStmt) {
	if (parentToChildRelMap.find(parentStmt) != parentToChildRelMap.end()) {
		return parentToChildRelMap[parentStmt].find(childStmt) != parentToChildRelMap[parentStmt].end();
	}

	return false;
}

list<int> ParentToChildTable::getAllParents() {
	return uniqueParentList;
}

pair<list<int>, list<int>> ParentToChildTable::getAllParentsRel() {
	return make_pair(parentList, childList);
}