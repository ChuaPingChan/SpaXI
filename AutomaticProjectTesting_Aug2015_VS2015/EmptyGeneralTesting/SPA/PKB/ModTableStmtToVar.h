#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ModTableStmtToVar {
public:
    ModTableStmtToVar();
    bool addModStmtToVarList(int stmtNumber, string var);
    list<string> getModVariablesFromStmt(int stmtNumber);
private:
    unordered_map<int, list<string>>modStmtToVarMap;
};