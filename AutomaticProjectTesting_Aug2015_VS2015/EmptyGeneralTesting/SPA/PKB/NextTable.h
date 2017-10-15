#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
};