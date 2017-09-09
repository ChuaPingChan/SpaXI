#include "UsesTableVarToStmt.h"

UsesTableVarToStmt::UsesTableVarToStmt() {

}

bool UsesTableVarToStmt::addUsesVarToStmtList(string var, int stmtNumber) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToStmtMap.find(var) == usesVarToStmtMap.end()) {
        usesVarToStmtMap[var] = list<int>();
        usesVarToStmtMap[var].push_back(stmtNumber);
        usesVarToStmtMap[var].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToStmtMap[var].push_back(stmtNumber);
        usesVarToStmtMap[var].unique();
        return true;
    }
    return false;
}

list<int> UsesTableVarToStmt::getUsesStmtNumbersFromVariable(string var) {
    return usesVarToStmtMap[var];
}