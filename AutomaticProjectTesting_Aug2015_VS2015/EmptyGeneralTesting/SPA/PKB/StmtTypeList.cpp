#include "StmtTypeList.h"

StmtTypeList::StmtTypeList() {

}

bool StmtTypeList::addToAssignStmtList(int stmt) {
    // if stmt number does not exists in assignment list, add to list
    if (find(assignStmtList.begin(), assignStmtList.end(), stmt) == assignStmtList.end()) {
        assignStmtList.push_back(stmt);
        return true;
    }
    return false;
}

bool StmtTypeList::addToWhileStmtList(int stmt, string var) {
    // if stmt number does not exists in assignment list, add to list
    if (whileStmtList.find(stmt) == whileStmtList.end()) {
        whileStmtList[stmt] = var;
        return true;
    }
    return false;
}

string StmtTypeList::getVarFromWhile(int stmt) {
    return whileStmtList[stmt];
}