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

    bool isChild(int childStmt);

    int getParent(int childStmt);

    unordered_map<int, int> getTable();

    list<int> getAllChildren();

private:
    unordered_map<int, int> childToParentMap;
    list<int> childList;
};