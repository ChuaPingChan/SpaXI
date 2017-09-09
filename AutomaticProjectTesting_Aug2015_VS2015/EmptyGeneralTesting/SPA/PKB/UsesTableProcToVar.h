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
    bool addUsesProcToVarList(string proc, string var);
    list<string> getUsesVariablesFromProc(string proc);
private:
    unordered_map<string, list<string>> usesProcToVarMap;
};