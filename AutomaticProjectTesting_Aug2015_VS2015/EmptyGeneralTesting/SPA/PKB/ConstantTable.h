#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class ConstantTable {
public:
    ConstantTable();
    bool addConstantList(int stmtNumber, int constant);
    list<int> getStmtConstants(int stmtNumber);
	list<int> getAllConstants();
    bool hasConstants(int stmtNumber, int constant);
private:
    unordered_map<int, list<int>> constantTableMap;
};