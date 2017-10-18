#include "UsesTableProcToVar.h"

UsesTableProcToVar::UsesTableProcToVar() {

}

bool UsesTableProcToVar::addUsesProcToVarList(int procIdx, int varIdx) {
    // if proc name does not exist as a key, create new list and insert data to hash map
    if (usesProcToVarMap.find(procIdx) == usesProcToVarMap.end()) {
        usesProcToVarMap[procIdx] = list<int>();
        usesProcToVarMap[procIdx].push_back(varIdx);
        usesProcToVarMap[procIdx].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        usesProcToVarMap[procIdx].push_back(varIdx);
        usesProcToVarMap[procIdx].unique();
        return true;
    }
    return false;
}

list<int> UsesTableProcToVar::getUsesVariablesFromProc(int procIdx) {
	if (usesProcToVarMap.find(procIdx) == usesProcToVarMap.end()) {
		return list<int>();
	}

    return usesProcToVarMap[procIdx];
}

bool UsesTableProcToVar::setMap(unordered_map<int, list<int>> targetMap) {
	usesProcToVarMap = targetMap;
	return true;
}

unordered_map<int, list<int>> UsesTableProcToVar::getMap() {
	return usesProcToVarMap;
}

bool UsesTableProcToVar::isUses(int procIdx, int varIdx) {
	return find(usesProcToVarMap[procIdx].begin(), usesProcToVarMap[procIdx].end(), varIdx) != usesProcToVarMap[procIdx].end();
}

bool UsesTableProcToVar::isUsingAnything(int procIdx) {
	return usesProcToVarMap.find(procIdx) != usesProcToVarMap.end();
}

list<int> UsesTableProcToVar::getProcThatUses() {
	list<int> procList;
	for (unordered_map<int, list<int>>::iterator it = usesProcToVarMap.begin(); it != usesProcToVarMap.end(); ++it) {
		int procIdx = (*it).first;
		procList.push_back(procIdx);
	}
	return procList;
}

pair<list<int>, list<int>> UsesTableProcToVar::getProcPair() {
	list<int> procList;
	list<int> varList;

	for (unordered_map<int, list<int>>::iterator it = usesProcToVarMap.begin(); it != usesProcToVarMap.end(); ++it) {
		int procIdx = (*it).first;
		list<int> currList = (*it).second;

		for (int var : currList) {
			procList.push_back(procIdx);
			varList.push_back(var);
		}
	}

	return make_pair(procList, varList);
}