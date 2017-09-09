#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ModTableVarToStmt {
public:
    ModTableVarToStmt();
    bool addModVarToStmtList(string var, int stmtNumber);
    list<int> getModStmtNumbersFromVariable(string var);

private:
    unordered_map<string, list<int>> modVarToStmtMap;
};