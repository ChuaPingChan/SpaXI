#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class UsesTableProcToVar {
public:
    UsesTableProcToVar();
    bool addUsesProcToVarList(int procIdx, int var);
    list<int> getUsesVariablesFromProc(int procIdx);
private:
    unordered_map<int, list<int>> usesProcToVarMap;
};