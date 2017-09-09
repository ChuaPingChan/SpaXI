#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class UsesTableStmtToVar {
public:
    UsesTableStmtToVar();
    bool addUsesStmtToVarList(int stmtNumber, string var);
    list<string> getUsesVariablesFromStmt(int stmtNumber);
private:
    unordered_map<int, list<string>>usesStmtToVarMap;
};