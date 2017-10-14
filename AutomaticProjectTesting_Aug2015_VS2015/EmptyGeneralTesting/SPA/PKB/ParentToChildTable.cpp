#include "ParentToChildTable.h"

using namespace std;

ParentToChildTable::ParentToChildTable()
{
}

bool ParentToChildTable::addParentChild(int parentStmt, int childStmt) 
{
	if (parentStmt == 0) {
		return true;
	}

	//If parent doesnt exist in map, create new parent
	if (parentToChildMap.find(parentStmt) == parentToChildMap.end()) {
		parentToChildMap[parentStmt] = list<int>();
		parentToChildMap[parentStmt].push_back(childStmt);
		return true;
	}

	else {
		parentToChildMap[parentStmt].push_back(childStmt);
		parentToChildMap[parentStmt].unique();
		return true;
	}

	return false;
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
	if (parentToChildMap.find(parentStmt) != parentToChildMap.end()) {
		unordered_map<int, list<int>>::iterator it;
		it = parentToChildMap.find(parentStmt);
		if (std::find(it->second.begin(), it->second.end(), childStmt) != it->second.end()) {
				return true;
		}
	}

	return false;
}

list<int> ParentToChildTable::getAllParents() {
	list<int> stmtList;
	for (std::unordered_map<int, list<int>>::iterator it = parentToChildMap.begin(); it != parentToChildMap.end(); ++it) {
		stmtList.push_back((*it).first);
	}
	return stmtList;
}

pair<list<int>, list<int>> ParentToChildTable::getAllParentsRel() {
	list<int> parent;
	list<int> child;

	for (std::unordered_map<int, list<int>>::iterator it = parentToChildMap.begin(); it != parentToChildMap.end(); ++it) {
		int currStmt = (*it).first;
		list<int> after = (*it).second;

		for (std::list<int>::iterator it2 = after.begin(); it2 != after.end(); ++it2) {
			parent.push_back(currStmt);
			child.push_back((*it2));
		}
	}

	pair<list<int>, list<int>> listPair = make_pair(parent, child);
	return listPair;
}