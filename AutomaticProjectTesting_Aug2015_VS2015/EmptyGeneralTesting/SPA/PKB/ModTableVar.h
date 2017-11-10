#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ModTableVar {
public:
    ModTableVar();
    bool addModVarToStmtList(int varIdx, int stmtNumber);
    bool addModVarToProcList(int varIdx, int proc);

    list<int> getModStmtsFromVar(int varIdx);
    list<int> getModProcsFromVar(int varIdx);
	bool setStmtMap(unordered_map<int, list<int>> map);
	bool setProcMap(unordered_map<int, list<int>> map);


private:
    unordered_map<int, list<int>> modVarToStmtMap;
    unordered_map<int, list<int>> modVarToProcMap;
};