#include "ModTableVarToStmt.h"

using namespace std;

ModTableVarToStmt::ModTableVarToStmt() {

}

bool ModTableVarToStmt::addModVarToStmtList(string var, int stmtNumber) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToStmtMap.find(var) == modVarToStmtMap.end()) {
        modVarToStmtMap[var] = list<int>();
        modVarToStmtMap[var].push_back(stmtNumber);
        modVarToStmtMap[var].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToStmtMap[var].push_back(stmtNumber);
        modVarToStmtMap[var].unique();
        return true;
    }
    return false;
}

list<int> ModTableVarToStmt::getModStmtNumbersFromVariable(string var) {
    return modVarToStmtMap[var];
}