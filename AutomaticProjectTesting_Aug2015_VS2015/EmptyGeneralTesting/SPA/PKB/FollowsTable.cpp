#include "FollowsTable.h"

using namespace std;

FollowsTable::FollowsTable(){
}

bool FollowsTable::addFollows(int stmt1, int stmt2, int stmt3)
{
	//replace no matter what
	followsMap[stmt1] = std::make_pair(stmt2, stmt3);
	return true;
}

int FollowsTable::getStmtBef(int stmt) {
	return followsMap[stmt].first;
}

int FollowsTable::getStmtAft(int stmt) {
	return followsMap[stmt].second;
}

unordered_map<int, pair<int, int>> FollowsTable::getMap() {
	return followsMap;
}

void FollowsTable::setMap(unordered_map<int, pair<int, int>> map) {
	followsMap = map;
}

bool FollowsTable::hasBefore(int afterStmt) {
	if (followsMap.find(afterStmt) != followsMap.end()) {
		if (followsMap[afterStmt].first != 0) {
			return true;
		}
	}

	return false;
}

bool FollowsTable::hasAfter(int beforeStmt) {
	if (followsMap.find(beforeStmt) != followsMap.end()) {
		if (followsMap[beforeStmt].second != 0) {
			return true;
		}
	}

	return false;
}

bool FollowsTable::isFollows(int stmt1, int stmt2) {
	if (followsMap.find(stmt1) != followsMap.end()) {
		if (followsMap[stmt1].second == stmt2) {
			return true;
		}
	}

	return false;
}

list<int> FollowsTable::getAllBefore() {
	list<int> stmtList;
	for (std::unordered_map<int, pair<int, int>>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int currStmt = (*it).first;
		int after = (*it).second.second;
		if (after != 0) {
			stmtList.push_back(currStmt);
		}
	}
	return stmtList;
}

list<int> FollowsTable::getAllAfter() {
	list<int> stmtList;
	for (std::unordered_map<int, pair<int, int>>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int currStmt = (*it).first;
		int before = (*it).second.first;
		if (before != 0) {
			stmtList.push_back(currStmt);
		}
	}
	return stmtList;
}

pair<list<int>, list<int>> FollowsTable::getAllFollows() {
	list<int> bef;
	list<int> aft;
	pair <list<int>, list<int>> stmtPair;

	for (std::unordered_map<int, pair<int, int>>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int before = (*it).first;
		int after = (*it).second.second;
		if (after != 0) {
			bef.push_back(before);
			aft.push_back(after);
		}
	}

	stmtPair = std::make_pair(bef, aft);
	return stmtPair;
}