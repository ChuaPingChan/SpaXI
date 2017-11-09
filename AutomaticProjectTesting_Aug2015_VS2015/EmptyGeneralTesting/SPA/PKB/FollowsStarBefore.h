#pragma once
#include <stdio.h>
#include <unordered_map>
#include <list>
#include <unordered_set>

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
	list<int> beforeList;
	list<int> afterList;
	unordered_map<int, unordered_set<int>> followsStarBeforeRelMap;
};