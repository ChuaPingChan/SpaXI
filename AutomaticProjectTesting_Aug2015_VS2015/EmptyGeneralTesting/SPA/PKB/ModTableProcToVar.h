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
    bool addModProcToVarList(int procIdx, string var);
    list<string> getModVariablesFromProc(int procIdx);
private:
    unordered_map<int, list<string>> modProcToVarMap;
};