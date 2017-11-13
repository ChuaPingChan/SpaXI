#include "ModTableVar.h"

using namespace std;

ModTableVar::ModTableVar() {

}

bool ModTableVar::addModVarToStmtList(int varIdx, int stmtNumber) {
    modVarToStmtMap[varIdx].push_back(stmtNumber);
    return true;
}

bool ModTableVar::addModVarToProcList(int varIdx, int proc)
{
    modVarToProcMap[varIdx].push_back(proc);
    return true;
}


list<int> ModTableVar::getModStmtsFromVar(int varIdx) {
    if (modVarToStmtMap.find(varIdx) == modVarToStmtMap.end()) {
        return list<int>();
    }

    return modVarToStmtMap[varIdx];
}

list<int> ModTableVar::getModProcsFromVar(int varIdx)
{
    if (modVarToProcMap.find(varIdx) == modVarToStmtMap.end()) {
        return list<int>();
    }
    return modVarToProcMap[varIdx];
}


bool ModTableVar::setStmtMap(unordered_map<int, list<int>> map) {
    modVarToStmtMap = map;
    return true;
}

bool ModTableVar::setProcMap(unordered_map<int, list<int>> map) {
    modVarToProcMap = map;
    return true;
}