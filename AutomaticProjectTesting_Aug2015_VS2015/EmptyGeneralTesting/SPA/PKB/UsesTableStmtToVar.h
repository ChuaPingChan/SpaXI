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
    bool addUsesStmtToVarList(int stmtNumber, string var);
    //
    bool isUses(int stmtNumber, string var);
    bool isUsingAnything(int stmtNumber);
    list<string> getUsesVariablesFromStmt(int stmtNumber);
    //
    list<int> getStmtThatUses();
    pair<list<int>,list<string>> getUsesPair();
private:
    unordered_map<int, list<string>>usesStmtToVarMap;
};