#include "IfStmt.h"

using namespace std;

/*
Sets up the ifStmt object with its required details
This IfStmt object is only used in the computation of affets and affects star
*/
IfStmt::IfStmt(int stmtNum, int branchIf, int endIf,
    int branchElse, int endElse, bool visitedElse, int afterIf,
    unordered_map<int, unordered_set<int>> ifLatestMod, unordered_map<int, unordered_set<int>> elseLatestMod) {
    this->stmtNum = stmtNum;
    this->branchIf = branchIf;
    this->endIf = endIf;
    this->branchElse = branchElse;
    this->endElse = endElse;
    this->visitedElse = visitedElse;
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
    ifLatestMod = newMap;
}

unordered_map<int, unordered_set<int>> IfStmt::getElseMap() {
    return elseLatestMod;
}

unordered_map<int, unordered_set<int>> IfStmt::getIfMap() {
    return ifLatestMod;
}

int IfStmt::getBranchElse() {
    return branchElse;
}

int IfStmt::getBranchIf() {
    return branchIf;
}

void IfStmt::visitElse() {
    visitedElse = true;
}

bool IfStmt::hasVisitedElse() {
    return visitedElse;
}

int IfStmt::getAfterIf() {
    return afterIf;
}

int IfStmt::getStmtNum() {
    return stmtNum;
}