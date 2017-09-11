#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class ChildToParentTable
{
public:
	ChildToParentTable();

	bool addChildParent(int childStmt, int parentStmt);

	int getParent(int childStmt);

private:
	unordered_map<int, int> childToParentMap;
};