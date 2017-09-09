#include "ModTableStmtToVar.h"

using namespace std;

ModTableStmtToVar::ModTableStmtToVar() {

}

bool ModTableStmtToVar::addModStmtToVarList(int stmtNumber, string var) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modStmtToVarMap.find(stmtNumber) == modStmtToVarMap.end()) {
        modStmtToVarMap[stmtNumber] = list<string>();
        modStmtToVarMap[stmtNumber].push_back(var);
        modStmtToVarMap[stmtNumber].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        modStmtToVarMap[stmtNumber].push_back(var);
        modStmtToVarMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<string> ModTableStmtToVar::getModVariablesFromStmt(int stmtNumber) {
    return modStmtToVarMap[stmtNumber];
}