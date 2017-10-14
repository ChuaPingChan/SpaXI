#include "ModTableProcToVar.h"

ModTableProcToVar::ModTableProcToVar() {

}

bool ModTableProcToVar::addModProcToVarList(int procIdx, int varIdx) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (modProcToVarMap.find(procIdx) == modProcToVarMap.end()) {
        modProcToVarMap[procIdx] = list<int>();
        modProcToVarMap[procIdx].push_back(varIdx);
        return true;
    }
    else {
        // else, expand the list of variables
        modProcToVarMap[procIdx].push_back(varIdx);
        return true;
    }
    return false;
}

list<int> ModTableProcToVar::getModVariablesFromProc(int procIdx) {
    return modProcToVarMap[procIdx];
}