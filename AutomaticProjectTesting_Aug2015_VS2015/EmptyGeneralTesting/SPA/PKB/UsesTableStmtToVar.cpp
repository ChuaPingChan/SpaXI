#include "UsesTableStmtToVar.h"

UsesTableStmtToVar::UsesTableStmtToVar() {

}

bool UsesTableStmtToVar::addUsesStmtToVarList(int stmtNumber, string var) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesStmtToVarMap.find(stmtNumber) == usesStmtToVarMap.end()) {
        usesStmtToVarMap[stmtNumber] = list<string>();
        usesStmtToVarMap[stmtNumber].push_back(var);
        usesStmtToVarMap[stmtNumber].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        usesStmtToVarMap[stmtNumber].push_back(var);
        usesStmtToVarMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<string> UsesTableStmtToVar::getUsesVariablesFromStmt(int stmtNumber) {
    return usesStmtToVarMap[stmtNumber];
}