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