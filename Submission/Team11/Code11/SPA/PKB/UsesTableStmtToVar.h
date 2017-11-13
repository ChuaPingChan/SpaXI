#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>

using namespace std;

class UsesTableStmtToVar {
public:
    UsesTableStmtToVar();
    bool addUsesStmtToVarList(int stmtNumber, int varIdx);
    //
    bool isUses(int stmtNumber, int varIdx);
    bool isUsingAnything(int stmtNumber);
    bool setMap(unordered_map<int, list<int>> map);
    unordered_map<int, list<int>> getMap();
    list<int> getUsesVariablesFromStmt(int stmtNumber);
    //
    list<int> getStmtThatUses();
    pair<list<int>, list<int>> getUsesPair();
private:
    unordered_map<int, list<int>>usesStmtToVarMap;
    unordered_map<int, unordered_set<int>> usesStmtToVarRelMap;
    list<int> usesStmtList;
    list<int> usesVarList;
    pair<list<int>, list<int>> usesStmtToVarPair;
};