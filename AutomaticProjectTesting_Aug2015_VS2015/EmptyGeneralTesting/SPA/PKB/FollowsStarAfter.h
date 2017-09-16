#pragma once
#include <stdio.h>
#include <unordered_map>
#include <list>

using namespace std;

class FollowsStarAfter {
public:
	FollowsStarAfter();

	void setMap(unordered_map<int, list<int>> targetMap);

	list<int> getAfterStar(int stmt);

	bool isAfterStar(int stmtBefore, int stmtAfter);

	list<int> getAllAfterStar();

	pair <list<int>, list<int>> getAllFollows();
private:
	unordered_map<int, list<int>> followsStarAfterMap;
};