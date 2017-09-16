#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class VarIdxTable {
public:
    VarIdxTable();
    bool addToVarIdxTable(string var);
    int getIdxFromVar(string var);
    bool isVarPresent(string var);
private:
    unordered_map<string, int> varIdxMap;
    int varIdx = 0;
};