#include "UsesTableVar.h"

UsesTableVar::UsesTableVar() {

}

bool UsesTableVar::addUsesVarToStmtList(int varIdx, int stmtNumber) {
    usesVarToStmtMap[varIdx].push_back(stmtNumber);
    return true;
}

bool UsesTableVar::addUsesVarToProcList(int varIdx, int proc)
{
    usesVarToProcMap[varIdx].push_back(proc);
    return true;
}

list<int> UsesTableVar::getUsesStmtsFromVar(int varIdx) {
    if (usesVarToStmtMap.find(varIdx) == usesVarToStmtMap.end()) {
        return list<int>();
    }
    return usesVarToStmtMap[varIdx];
}

list<int> UsesTableVar::getUsesProcsFromVar(int varIdx)
{
    if (usesVarToProcMap.find(varIdx) == usesVarToProcMap.end()) {
        return list<int>();
    }
    return usesVarToProcMap[varIdx];
}


bool UsesTableVar::setStmtMap(unordered_map<int, list<int>> map) {
    usesVarToStmtMap = map;
    return true;
}

bool UsesTableVar::setProcMap(unordered_map<int, list<int>> map) {
    usesVarToProcMap = map;
    return true;
}
