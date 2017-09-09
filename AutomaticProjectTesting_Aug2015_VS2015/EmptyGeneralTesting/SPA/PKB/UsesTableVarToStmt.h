#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class UsesTableVarToStmt {
public:
    UsesTableVarToStmt();
    bool addUsesVarToStmtList(string var, int stmtNumber);
    list<int> getUsesStmtNumbersFromVariable(string var);

private:
    unordered_map<string, list<int>> usesVarToStmtMap;
};