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

void ParentToChildStarTable::setMap(unordered_map<int, list<int>> target) {
	parentToChildStarMap = target;
}

bool ParentToChildStarTable::isParentStar(int parentStmt, int childStmt) {
	if (parentToChildStarMap.find(parentStmt) != parentToChildStarMap.end()) {
		if (std::find(parentToChildStarMap[parentStmt].begin(), 
			parentToChildStarMap[parentStmt].end(), childStmt) != parentToChildStarMap[parentStmt].end()) {
			return true;
		}
	}

	return false;
}

bool ParentToChildStarTable::isParentStarChild(int parentStmt, int childStmt) {
	if (parentToChildStarMap.find(parentStmt) != parentToChildStarMap.end()) {
		unordered_map<int, list<int>>::iterator it;
		it = parentToChildStarMap.find(parentStmt);
		if (std::find(it->second.begin(), it->second.end(), childStmt) != it->second.end()) {
			return true;
		}
	}
	return false;
}