#include "FollowsStarBefore.h"

using namespace std;

FollowsStarBefore::FollowsStarBefore() {
}

void FollowsStarBefore::setMap(unordered_map<int, list<int>> targetMap) {
	followsStarBeforeMap = targetMap;
}

list<int> FollowsStarBefore::getBeforeStar(int stmt) {
	if (followsStarBeforeMap.find(stmt) == followsStarBeforeMap.end()) {
		list<int> emptyList;
		return emptyList;
	}

	return followsStarBeforeMap[stmt];
}

bool FollowsStarBefore::isBeforeStar(int stmtBefore, int stmtAfter) {
	if (followsStarBeforeMap.find(stmtAfter) != followsStarBeforeMap.end()) {
		unordered_map<int, list<int>>::iterator it;
		it = followsStarBeforeMap.find(stmtAfter);
		if (std::find(it->second.begin(), it->second.end(), stmtBefore) != it->second.end()) {
			return true;
		}
	}
	return false;
}

list<int> FollowsStarBefore::getAllBeforeStar() {
	list<int> stmtList;
	for (std::unordered_map<int, list<int>>::iterator it = followsStarBeforeMap.begin(); it != followsStarBeforeMap.end(); ++it) {
		int currStmt = (*it).first;
		list<int> after = (*it).second;
		stmtList.insert(stmtList.end(), after.begin(), after.end());
		stmtList.sort();
		stmtList.unique();
	}
	return stmtList;
}