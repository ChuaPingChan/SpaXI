#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>

using namespace std;

class NextStarCache
{
public:
	NextStarCache();

	bool isComputedBefore(int stmtBef);

	bool computeStmtBef(int stmtBef, unordered_map<int, list<int>> nextMap);

	bool computeStmtAft(int stmtAft, unordered_map<int, list<int>> nextMapReverse);

private:
	unordered_map<int, list<int>> nextStarMap;
	unordered_map<int, list<int>> nextStarMapReverse;
};