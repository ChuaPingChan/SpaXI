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
    bool addModStmtToVarList(int stmtNumber, int varIdx);
    //
    bool isMod(int stmtNumber, int varIdx);
    bool isModifyingAnything(int stmtNumber);
    list<int> getModVariablesFromStmt(int stmtNumber);
    //
    list<int> getStmtThatModifies();
    pair<list<int>,list<int>> getModPair();
    
private:
    unordered_map<int, list<int>>modStmtToVarMap;
};