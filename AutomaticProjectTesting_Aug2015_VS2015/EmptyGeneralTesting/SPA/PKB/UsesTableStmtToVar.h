#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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
    list<int> getUsesVariablesFromStmt(int stmtNumber);
    //
    list<int> getStmtThatUses();
    pair<list<int>,list<int>> getUsesPair();
private:
    unordered_map<int, list<int>>usesStmtToVarMap;
};