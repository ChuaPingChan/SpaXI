#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class CallsTable
{
public:
	CallsTable();
	bool addCallsRel(int caller, int callee);
	bool addCallsStmt(int stmt, int callee);
	bool isCaller(int caller);
	bool isCallee(int callee);
	list<int> getCallee(int caller);
	list<int> getCaller(int callee);
	bool isCalls(int caller, int callee);
	bool hasCalls();
	list<int> getAllCallees();
	list<int> getAllCallers();
private:
	unordered_map<int, list<int>> callsProcMap;
	unordered_map<int, list<int>> callsProcMapReverse;
	unordered_map<int, int> callsStmtToProcMap;
	unordered_map<int, list<int>> callsProcToStmtMap;
	unordered_map <string, bool> callsRelPairs;
	list<int> callees;
	list<int> callers;
};