#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class UsesTableVar {
public:
    UsesTableVar();
    bool addUsesVarToStmtList(int varIdx, int stmtNumber);
    bool addUsesVarToProcList(int varIdx, int proc);

    list<int> getUsesStmtsFromVar(int varIdx);
    list<int> getUsesProcsFromVar(int varIdx);
    bool setStmtMap(unordered_map<int, list<int>> map);
    bool setProcMap(unordered_map<int, list<int>> map);

private:
    unordered_map<int, list<int>> usesVarToStmtMap;
    unordered_map<int, list<int>> usesVarToProcMap;
};