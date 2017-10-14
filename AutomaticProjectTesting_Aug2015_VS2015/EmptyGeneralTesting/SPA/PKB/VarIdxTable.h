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
	string getVarFromIdx(int idx);
    bool isVarPresent(string var);
	list<string> getAllVariables();
	list<int> getAllVariablesIndex();
private:
    unordered_map<string, int> varIdxMap;
	unordered_map<int, string> varIdxToStringMap;
    int varIdx = 0;
	list<int> allVarIdx;
	list<string> allVarString;
};