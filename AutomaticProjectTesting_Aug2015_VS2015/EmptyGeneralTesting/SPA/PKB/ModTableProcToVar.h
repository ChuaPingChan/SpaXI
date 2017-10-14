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
    bool addModProcToVarList(int procIdx, int varIdx);
    list<int> getModVariablesFromProc(int procIdx);
	unordered_map<int, list<int>> getMap();
	bool isMod(int procIdx, int varIdx);
	bool setMap(unordered_map<int, list<int>> map);
	bool isModifyingAnything(int procIdx);
	list<int> getProcThatModifies();
	pair<list<int>, list<int>> getProcPair();
private:
    unordered_map<int, list<int>> modProcToVarMap;
};