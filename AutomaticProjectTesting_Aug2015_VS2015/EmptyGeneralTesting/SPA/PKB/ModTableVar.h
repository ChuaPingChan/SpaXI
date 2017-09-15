#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ModTableVar {
public:
    ModTableVar();
    bool addModVarToStmtList(int varIdx, int stmtNumber);
    bool addModVarToProcList(int varIdx, string proc);
    bool addModVarToAssignList(int varIdx, int stmtNumber);
    bool addModVarToWhileStmtList(int varIdx, int stmtNumber);
    bool addModVarToWhileContainerMap(int varIdx, int stmtNumber);

    list<int> getModStmtsFromVar(int varIdx);
    list<string> getModProcsFromVar(int varIdx);
    list<int> getModAssignsFromVar(int varIdx);
    list<int> getModWhileStmtFromVar(int varIdx);
    list<int> getModWhileContainersFromVar(int varIdx);


private:
    unordered_map<int, list<int>> modVarToStmtMap;
    unordered_map<int, list<string>> modVarToProcMap;
    unordered_map<int, list<int>> modVarToAssignMap;
    unordered_map<int, list<int>> modVarToWhileStmtMap;
    unordered_map<int, list<int>> modVarToWhileContainerMap;
};