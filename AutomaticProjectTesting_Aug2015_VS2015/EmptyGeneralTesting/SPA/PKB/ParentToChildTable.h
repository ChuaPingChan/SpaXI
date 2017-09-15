#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ParentToChildTable 
{
public:
	ParentToChildTable();

	bool addParentChild(int parentStmt, int childStmt);

	list<int> getChildren(int parentStmt);

private:
	unordered_map<int, list<int>> parentToChildMap;
};