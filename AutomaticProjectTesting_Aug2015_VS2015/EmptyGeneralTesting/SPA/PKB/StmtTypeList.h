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
	bool addToCallsStmtList(int stmt, int calleeProcIdx, string calleeProcName);
	list<int> getStmtFromCalleeProcName(string calleeProcName);
	int getProcIdxFromCall(int stmt);
	list<string> getAllCalleeNames();
	unordered_map<int, int> getCallToProcIdxMap();
	bool addToIfStmtList(int stmt);
	list<int> getAllStatements();
	bool isStatement(int stmt);
	bool isAssignStmt(int stmt);
    bool isWhileStmt(int stmt);
	bool isCallsStmt(int stmt);
    bool isPresent(int stmt);
    bool isIfStmt(int stmt);
    list<int> getAssignStmtList();
    list<int> getWhileStmtList();
    list<int> getIfStmtList();
	list<int> getCallsStmtList();
    list<int> getStmtType(list<int> stmtList, Entity type);
    pair<list<int>, list<int>> getStmtType(pair<list<int>, list<int>> pairOfList, Entity type);
	pair<list<int>, list<int>> getStmtType(pair<list<int>, list<int>> pairOfList, Entity type1, Entity type2);
	list<int> getStmtType(int stmt, Entity type);
private:
	list<int> allStmtList;
    list<int> assignStmtList;
    list<int> whileStmtList;
	list<int> callsStmtList;
    list<int> ifStmtList;
	list<string> allCalleeName;
	unordered_map<int, string> callToProcNameMap;
	unordered_map<string, list<int>> procNameToCallMap;
	unordered_map<int, int> callToProcIdxMap;
};