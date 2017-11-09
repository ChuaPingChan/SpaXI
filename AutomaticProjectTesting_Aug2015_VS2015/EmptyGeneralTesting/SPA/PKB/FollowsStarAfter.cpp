#include "FollowsStarAfter.h"

using namespace std;

FollowsStarAfter::FollowsStarAfter() {
}

/*
Populate required information
*/
void FollowsStarAfter::setMap(unordered_map<int, list<int>> targetMap) {
	int before;
	for (auto it : targetMap) {
		before = it.first;
		list<int> targetList = it.second;
		for (int after : targetList) {
			beforeList.push_back(before);
			afterList.push_back(after);
			followsStarAfterRelMap[before].insert(after);
		}
	}

	allFollowsStarPair = make_pair(beforeList, afterList);
	beforeList.sort();
	beforeList.unique();
	afterList.sort();
	afterList.unique();
	followsStarAfterMap = targetMap;
}

list<int> FollowsStarAfter::getAfterStar(int stmt) {
	if (followsStarAfterMap.find(stmt) == followsStarAfterMap.end()) {
		return list<int>();
	}

	return followsStarAfterMap[stmt];
}

bool FollowsStarAfter::isAfterStar(int stmtBefore, int stmtAfter) {
	if (followsStarAfterRelMap.find(stmtBefore) != followsStarAfterRelMap.end()) {
		return followsStarAfterRelMap[stmtBefore].find(stmtAfter) != followsStarAfterRelMap[stmtBefore].end();
	}
	return false;
}

list<int> FollowsStarAfter::getAllAfterStar() {
	return afterList;
}

pair<list<int>, list<int>> FollowsStarAfter::getAllFollows() {
	return allFollowsStarPair;
}