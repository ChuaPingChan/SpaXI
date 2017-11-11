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

class ModTableStmtToVar {
public:
    ModTableStmtToVar();
    bool addModStmtToVarList(int stmtNumber, int varIdx);
    //
    bool isMod(int stmtNumber, int varIdx);
    bool isModifyingAnything(int stmtNumber);
    bool setMap(unordered_map<int, list<int>> map);
    unordered_map<int, list<int>> getMap();
    list<int> getModVariablesFromStmt(int stmtNumber);
    list<int> getStmtThatModifies();
    pair<list<int>, list<int>> getModPair();

private:
    unordered_map<int, list<int>>modStmtToVarMap;
    unordered_map<int, unordered_set<int>> modStmtToVarRelMap;
    pair<list<int>, list<int>> modStmtToVarPair;
    list<int> modStmtList;
    list<int> modVarList;
};