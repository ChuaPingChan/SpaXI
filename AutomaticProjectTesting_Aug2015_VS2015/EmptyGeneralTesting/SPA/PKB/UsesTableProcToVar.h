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
	bool setMap(unordered_map<int, list<int>> targetMap);
	unordered_map<int, list<int>> getMap();
	bool isUses(int procIdx, int varIdx);
	bool isUsingAnything(int procIdx);
	list<int> getProcThatUses();
	pair<list<int>, list<int>> getProcPair();
private:
    unordered_map<int, list<int>> usesProcToVarMap;
};