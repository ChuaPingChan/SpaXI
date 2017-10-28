#include "IfStmt.h"

using namespace std;

IfStmt::IfStmt(int stmtNum, int branchIf, int endIf,
	int branchElse, int endElse, bool visitedElse, int afterIf,
	unordered_map<int, unordered_set<int>> ifLatestMod, unordered_map<int, unordered_set<int>> elseLatestMod) {
	this->stmtNum = stmtNum;
	this->branchIf = branchIf;
	this->endIf = endIf;
	this->branchElse = branchElse;
	this->endElse = endElse;
	this->afterIf = afterIf;
	this->ifLatestMod = ifLatestMod;
	this->elseLatestMod = elseLatestMod;
}

bool IfStmt::isEndIf(int target) {
	return (target == endIf);
}

bool IfStmt::isEndElse(int target) {
	return (target == endElse);
}

void IfStmt::setIfMap(unordered_map<int, unordered_set<int>> newMap) {
	this->ifLatestMod = newMap;
}

unordered_map<int, unordered_set<int>> IfStmt::getElseMap() {
	return elseLatestMod;
}

int IfStmt::getBranchElse() {
	return branchElse;
}

void IfStmt::visitElse() {
	visitedElse = true;
}