#include "CallsTable.h"

using namespace std;

CallsTable::CallsTable() {
}

bool CallsTable::addCallsRel(int caller, int callee) {
	if (callsProcMap.find(caller) == callsProcMap.end()) {
		callers.push_back(caller);
	}

	if (callsProcMapReverse.find(callee) == callsProcMapReverse.end()) {
		callees.push_back(callee);
	}

	allCalls.first.push_back(caller);
	allCalls.second.push_back(callee);
	callsProcMap[caller].push_back(callee);
	callsProcMapReverse[callee].push_back(caller);
	string callsRel = to_string(caller) + "," + to_string(callee);
	callsRelPairs[callsRel] = true;
	return true;
}

bool CallsTable::addCallsStmt(int stmt, int callee) {
	callsStmtToProcMap[stmt] = callee;
	if (callsProcToStmtMap[callee].empty()) {
		callsProcToStmtMap[callee].push_back(stmt);
		return true;
	}

	else {
		callsProcToStmtMap[callee].push_back(stmt);
		return true;
	}

	return false;
}

bool CallsTable::isCaller(int caller) {
	return (callsProcMap.find(caller) != callsProcMap.end());
}

bool CallsTable::isCallee(int callee) {
	return (callsProcMapReverse.find(callee) != callsProcMapReverse.end());
}

list<int> CallsTable::getCallee(int caller) {
	if (callsProcMap.find(caller) == callsProcMap.end()) {
		return list<int>();
	}

	return callsProcMap[caller];
}

list<int> CallsTable::getCaller(int callee) {
	if (callsProcMapReverse.find(callee) == callsProcMapReverse.end()) {
		return list<int>();
	}

	return callsProcMapReverse[callee];
}

bool CallsTable::isCalls(int caller, int callee) {
	string callsRel = to_string(caller) + "," + to_string(callee);
	return (callsRelPairs.find(callsRel) != callsRelPairs.end());
}

bool CallsTable::hasCalls() {
	return !callsProcMap.empty();
}

list<int> CallsTable::getAllCallees() {
	return callees;
}

list<int> CallsTable::getAllCallers() {
	return callers;
}

pair<list<int>, list<int>> CallsTable::getAllCalls() {
	return allCalls;
}

unordered_map<int, list<int>> CallsTable::getTable() {
	return callsProcMap;
}

unordered_map<int, list<int>> CallsTable::getTableReverse() {
	return callsProcMapReverse;
}