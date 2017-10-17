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
	if (modProcToVarMap.find(procIdx) == modProcToVarMap.end()) {
		return list<int>();
	}

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

bool ModTableProcToVar::isModifyingAnything(int procIdx) {
	return modProcToVarMap.find(procIdx) != modProcToVarMap.end();
}

list<int> ModTableProcToVar::getProcThatModifies() {
	list<int> procList;
	for (unordered_map<int, list<int>>::iterator it = modProcToVarMap.begin(); it != modProcToVarMap.end(); ++it) {
		int procIdx = (*it).first;
		procList.push_back(procIdx);
	}

	return procList;
}

pair<list<int>, list<int>> ModTableProcToVar::getProcPair() {
	list<int> procList;
	list<int> varList;

	for (unordered_map<int, list<int>>::iterator it = modProcToVarMap.begin(); it != modProcToVarMap.end(); ++it) {
		int procIdx = (*it).first;
		list<int> currList = (*it).second;

		for (int var : currList) {
			procList.push_back(procIdx);
			varList.push_back(var);
		}
	}

	return make_pair(procList, varList);
}