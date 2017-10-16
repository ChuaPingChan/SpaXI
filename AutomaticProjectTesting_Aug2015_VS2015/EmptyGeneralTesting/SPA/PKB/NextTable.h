#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "NextStarCache.h"

using namespace std;

class NextTable
{
public:
	NextTable();
	bool setNextRel(int stmt, int stmtNext);
	bool isNext(int stmtBef, int stmtAft);
	bool isExecutedBefore(int stmtBef);
	pair<list<int>, list<int>> getAllNext();
	bool isNextStar(int stmtBef, int stmtAft, NextStarCache & nextStarCache);
	list<int> getExecutedAfter(int stmtBef);
	bool hasNext();
	list<int> getAllExecutedAfter();
	list<int> getExecutedBefore(int stmtAft);
	list<int> getExecutedBefore();
	bool isExecutedAfter(int stmtAft);
	list<int> getAllExecutedBefore();
private:
	unordered_map<int, list<int>> nextMap;
	unordered_map<int, list<int>> nextMapReverse;
	list<int> prevList;
	list<int> nextList;
	unordered_set<string> allNextRel;
};