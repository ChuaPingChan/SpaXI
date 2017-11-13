#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class ConstantTable {
public:
    ConstantTable();
    bool addConstantList(int constant);
    list<int> getAllConstants();
    bool isConstant(int constant);
private:
    unordered_set<int> constantSet;
    list<int> constantList;
};