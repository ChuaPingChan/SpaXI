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

class IfStmt
{
public:
	IfStmt(int stmtNum, int branchIf, int endIf,
		int branchElse, int endElse, bool visitedElse, int afterIf,
		unordered_map<int, unordered_set<int>> ifLatestMod, unordered_map<int, unordered_set<int>> elseLatestMod);

	bool isEndIf(int target);

	bool isEndElse(int target);

	void setIfMap(unordered_map<int, unordered_set<int>> newMap);

	unordered_map<int, unordered_set<int>> getElseMap();

	int getBranchElse();

	void visitElse();


private:
	int stmtNum;
	int branchIf;
	int endIf;
	int branchElse;
	int endElse;
	bool visitedElse;
	int afterIf;
	unordered_map<int, unordered_set<int>> ifLatestMod;
	unordered_map<int, unordered_set<int>> elseLatestMod;
};