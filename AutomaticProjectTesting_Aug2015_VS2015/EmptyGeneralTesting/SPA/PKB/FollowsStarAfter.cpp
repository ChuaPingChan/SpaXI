#include "FollowsStarAfter.h"

FollowsStarAfter::FollowsStarAfter() {
}

void FollowsStarAfter::setMap(unordered_map<int, list<int>> targetMap) {
	followsStarAfterMap = targetMap;
}

list<int> FollowsStarAfter::getAfterStar(int stmt) {
	if (followsStarAfterMap.find(stmt) == followsStarAfterMap.end()) {
		list<int> emptyList;
		return emptyList;
	}

	return followsStarAfterMap[stmt];
}

bool FollowsStarAfter::isAfterStar(int stmtBefore, int stmtAfter) {
	if (followsStarAfterMap.find(stmtBefore) != followsStarAfterMap.end()) {
		unordered_map<int, list<int>>::iterator it;
		it = followsStarAfterMap.find(stmtBefore);
		if (std::find(it->second.begin(), it->second.end(), stmtAfter) != it->second.end()) {
			return true;
		}
	}
	return false;
}