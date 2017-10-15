#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class NextTable
{
public:
	NextTable();
	bool setNextRel(int stmt, int stmtNext);
private:
	unordered_map<int, list<int>> nextMap;
	unordered_map<int, list<int>> nextMapReverse;
	list<int> prevList;
	list<int> nextList;
	unordered_set<string> allNextRel;
};