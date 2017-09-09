#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ModTableProcToVar {
public:
    ModTableProcToVar();
    bool addModProcToVarList(string proc, string var);
    list<string> getModVariablesFromProc(string proc);
private:
    unordered_map<string, list<string>> modProcToVarMap;
};