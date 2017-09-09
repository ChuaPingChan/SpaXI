#include "UsesTableProcToVar.h"

UsesTableProcToVar::UsesTableProcToVar() {

}

bool UsesTableProcToVar::addUsesProcToVarList(string proc, string var) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (usesProcToVarMap.find(proc) == usesProcToVarMap.end()) {
        usesProcToVarMap[proc] = list<string>();
        usesProcToVarMap[proc].push_back(var);
        usesProcToVarMap[proc].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        usesProcToVarMap[proc].push_back(var);
        usesProcToVarMap[proc].unique();
        return true;
    }
    return false;
}

list<string> UsesTableProcToVar::getUsesVariablesFromProc(string proc) {
    return usesProcToVarMap[proc];
}