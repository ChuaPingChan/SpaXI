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

unordered_map<int, list<int>> ModTableProcToVar::getMap() {
	return modProcToVarMap;
}

bool ModTableProcToVar::isMod(int procIdx, int varIdx) {
	return find(modProcToVarMap[procIdx].begin(), modProcToVarMap[procIdx].end(), varIdx) != modProcToVarMap[procIdx].end();
}

bool ModTableProcToVar::setMap(unordered_map<int, list<int>> map) {
	modProcToVarMap = map;
	return true;
}