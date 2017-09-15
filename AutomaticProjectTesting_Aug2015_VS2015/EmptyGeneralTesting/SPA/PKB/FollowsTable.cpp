#include "FollowsTable.h"

using namespace std;

FollowsTable::FollowsTable(){
}

bool FollowsTable::addFollows(int stmt1, int stmt2, int stmt3)
{
	//If parent doesnt exist in map, create new parent
	if (followsMap.find(stmt1) == followsMap.end()) {
		followsMap[stmt1] = std::make_pair(stmt2, stmt3);
		return true;
	}

	return false;
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