#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class ParentToChildTable 
{
public:
	ParentToChildTable();

	bool addParentChild(int parentStmt, int childStmt);

	bool isParent(int parentStmt);

	bool empty();

	list<int> getChildren(int parentStmt);

	unordered_map<int, list<int>> getTable();

	bool isParentChild(int parentStmt, int childStmt);

	list<int> getAllParents();

	pair<list<int>, list<int>> getAllParentsRel();

private:
	unordered_map<int, list<int>> parentToChildMap;
	unordered_map<int, unordered_set<int>> parentToChildRelMap;
	list<int> parentList;
	list<int> uniqueParentList;
	list<int> childList;

};