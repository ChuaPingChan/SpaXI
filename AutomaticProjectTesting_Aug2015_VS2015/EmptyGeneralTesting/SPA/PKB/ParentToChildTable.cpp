#include "ParentToChildTable.h"

using namespace std;

ParentToChildTable::ParentToChildTable()
{
}

bool ParentToChildTable::addParentChild(int parentStmt, int childStmt) 
{
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

list<int> ParentToChildTable::getChildren(int parentStmt) {
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
}