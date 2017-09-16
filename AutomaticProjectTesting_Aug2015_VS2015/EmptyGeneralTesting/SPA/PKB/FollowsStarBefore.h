#pragma once
#include <stdio.h>
#include <unordered_map>
#include <list>

using namespace std;

class FollowsStarBefore {
public:
	FollowsStarBefore();

	void setMap(unordered_map<int, list<int>> targetMap);

	list<int> getBeforeStar(int stmt);

	bool isBeforeStar(int stmtBefore, int stmtAfter);

	list<int> getAllBeforeStar();

private:
	unordered_map<int, list<int>> followsStarBeforeMap;
};