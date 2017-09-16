#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ParentToChildStarTable
{
public:
	ParentToChildStarTable();

	bool addParentChild(int parentStmt, int childStmt);

	list<int> getChildren(int parentStmt);

	void setMap(unordered_map<int, list<int>> target);

	bool isParentStarChild(int parentStmt, int childStmt);

	pair<list<int>, list<int>> getAllParentStarRel();

private:
	unordered_map<int, list<int>> parentToChildStarMap;
};