#include "UsesTableProcToVar.h"

UsesTableProcToVar::UsesTableProcToVar() {

}

bool UsesTableProcToVar::addUsesProcToVarList(int procIdx, string var) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (usesProcToVarMap.find(procIdx) == usesProcToVarMap.end()) {
        usesProcToVarMap[procIdx] = list<string>();
        usesProcToVarMap[procIdx].push_back(var);
        usesProcToVarMap[procIdx].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        usesProcToVarMap[procIdx].push_back(var);
        usesProcToVarMap[procIdx].unique();
        return true;
    }
    return false;
}

list<string> UsesTableProcToVar::getUsesVariablesFromProc(int procIdx) {
    return usesProcToVarMap[procIdx];
}