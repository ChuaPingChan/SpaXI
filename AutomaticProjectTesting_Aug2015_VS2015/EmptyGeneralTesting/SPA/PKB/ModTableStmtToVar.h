#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

class ModTableStmtToVar {
public:
    ModTableStmtToVar();
    bool addModStmtToVarList(int stmtNumber, string var);
    //
    bool isMod(int stmtNumber, string var);
    bool isModifyingAnything(int stmtNumber);
    list<string> getModVariablesFromStmt(int stmtNumber);
    //
    list<int> getStmtThatModifies();
    pair<list<int>,list<string>> getModPair();
    
private:
    unordered_map<int, list<string>>modStmtToVarMap;
};