#include "ModTableProcToVar.h"

ModTableProcToVar::ModTableProcToVar() {

}

bool ModTableProcToVar::addModProcToVarList(string proc, string var) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (modProcToVarMap.find(proc) == modProcToVarMap.end()) {
        modProcToVarMap[proc] = list<string>();
        modProcToVarMap[proc].push_back(var);
        modProcToVarMap[proc].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        modProcToVarMap[proc].push_back(var);
        modProcToVarMap[proc].unique();
        return true;
    }
    return false;
}

list<string> ModTableProcToVar::getModVariablesFromProc(string proc) {
    return modProcToVarMap[proc];
}