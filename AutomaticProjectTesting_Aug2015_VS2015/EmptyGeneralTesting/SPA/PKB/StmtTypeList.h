#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <utility>
#include "../Entity.h"

using namespace std;

class StmtTypeList {
public:
    StmtTypeList();
    bool addToAssignStmtList(int stmt);
    bool addToWhileStmtList(int stmt);
	list<int> getAllStatements();
    bool isAssignStmt(int stmt);
    bool isWhileStmt(int stmt);
    bool isPresent(int stmt);
    list<int> getAssignStmtList();
    list<int> getWhileStmtList();
    list<int> getStmtType(list<int> stmtList, Entity type);
    pair<list<int>, list<string>> getStmtType(pair<list<int>, list<string>> pairOfList, Entity type);
private:
    list<int> assignStmtList;
    list<int> whileStmtList;
};