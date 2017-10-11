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
    bool addUsesVarToProcList(int varIdx, string proc);
    bool addUsesVarToAssignList(int varIdx, int stmtNumber);
    bool addUsesVarToWhileStmtList(int varIdx, int stmtNumber);
    bool addUsesVarToWhileContainerMap(int varIdx, int stmtNumber);
    bool addUsesVarToIfMap(int varIdx, int stmtNumber);

    list<int> getUsesStmtsFromVar(int varIdx);
    list<string> getUsesProcsFromVar(int varIdx);
    list<int> getUsesAssignsFromVar(int varIdx);
    list<int> getUsesWhileStmtFromVar(int varIdx);
    list<int> getUsesWhileContainersFromVar(int varIdx);
    list<int> getUsesIfFromVar(int varIdx);


private:
    unordered_map<int, list<int>> usesVarToStmtMap;
    unordered_map<int, list<string>> usesVarToProcMap;
    unordered_map<int, list<int>> usesVarToAssignMap;
    unordered_map<int, list<int>> usesVarToWhileStmtMap;
    unordered_map<int, list<int>> usesVarToWhileContainerMap;
    unordered_map<int, list<int>> usesVarToIfMap;
};