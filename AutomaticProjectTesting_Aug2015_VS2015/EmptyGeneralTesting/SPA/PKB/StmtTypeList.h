#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class StmtTypeList {
public:
    StmtTypeList();
    bool addToAssignStmtList(int stmt);
    bool addToWhileStmtList(int stmt, string var);
    string getVarFromWhile(int stmt);
private:
    vector<int> assignStmtList;
    unordered_map<int, string> whileStmtList;
};