#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ChildToParentStarTable
{
public:
	ChildToParentStarTable();

	list<int> getParentStar(int childStmt);

	void setMap(unordered_map<int, list<int>> target);

	bool isParentStar(int parentStmt, int childStmt);

private:
	unordered_map<int, list<int>> childToParentStarMap;
};