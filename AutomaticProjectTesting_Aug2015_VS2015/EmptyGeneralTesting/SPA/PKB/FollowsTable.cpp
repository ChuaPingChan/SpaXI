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