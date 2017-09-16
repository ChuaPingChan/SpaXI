#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <utility>

using namespace std;

class StmtTypeList {
public:
    StmtTypeList();
    bool addToAssignStmtList(int stmt);
    bool addToWhileStmtList(int stmt);
    bool isAssignStmt(int stmt);
    bool isWhileStmt(int stmt);
    bool isPresent(int stmt);
    list<int> getAssignStmtList();
    list<int> getWhileStmtList();
private:
    list<int> assignStmtList;
    list<int> whileStmtList;
};