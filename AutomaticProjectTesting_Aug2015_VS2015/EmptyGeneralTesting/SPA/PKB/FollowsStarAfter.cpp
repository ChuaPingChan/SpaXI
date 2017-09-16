#include "FollowsStarAfter.h"

using namespace std;

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

list<int> FollowsStarAfter::getAllAfterStar() {
	list<int> stmtList;
	for (std::unordered_map<int, list<int>>::iterator it = followsStarAfterMap.begin(); it != followsStarAfterMap.end(); ++it) {
		int currStmt = (*it).first;
		list<int> after = (*it).second;
		stmtList.insert(stmtList.end(), after.begin(), after.end());
		stmtList.sort();
		stmtList.unique();
	}
	return stmtList;
}

pair<list<int>, list<int>> FollowsStarAfter::getAllFollows() {
	list<int> bef;
	list<int> aft;

	for (std::unordered_map<int, list<int>>::iterator it = followsStarAfterMap.begin(); it != followsStarAfterMap.end(); ++it) {
		int currStmt = (*it).first;
		list<int> after = (*it).second;

		for (std::list<int>::iterator it2 = after.begin(); it2 != after.end(); ++it2) {
			bef.push_back(currStmt);
			aft.push_back((*it2));
		}
	}

	return make_pair(bef, aft);
}