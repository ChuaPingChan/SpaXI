#include "ModTableProcToVar.h"

ModTableProcToVar::ModTableProcToVar() {

}

bool ModTableProcToVar::addModProcToVarList(int procIdx, string var) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (modProcToVarMap.find(procIdx) == modProcToVarMap.end()) {
        modProcToVarMap[procIdx] = list<string>();
        modProcToVarMap[procIdx].push_back(var);
        modProcToVarMap[procIdx].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        modProcToVarMap[procIdx].push_back(var);
        modProcToVarMap[procIdx].unique();
        return true;
    }
    return false;
}

list<string> ModTableProcToVar::getModVariablesFromProc(int procIdx) {
    return modProcToVarMap[procIdx];
}