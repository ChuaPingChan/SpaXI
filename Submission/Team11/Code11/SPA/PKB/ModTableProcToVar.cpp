#include "ModTableProcToVar.h"

ModTableProcToVar::ModTableProcToVar() {

}

/*
Adds the following relations to modified table
*/
bool ModTableProcToVar::addModProcToVarList(int procIdx, int varIdx) {
    modProcToVarMap[procIdx].push_back(varIdx);
    modProcToVarMap[procIdx].sort();
    modProcToVarMap[procIdx].unique();
    modProcToVarRelMap[procIdx].insert(varIdx);
    return true;
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
    if (modProcToVarRelMap.find(procIdx) != modProcToVarRelMap.end()) {
        return modProcToVarRelMap[procIdx].find(varIdx) != modProcToVarRelMap[procIdx].end();
    }
    return false;
}

/*
Iterate the new map and populate the required information for modifies table
*/
bool ModTableProcToVar::setMap(unordered_map<int, list<int>> map) {
    int key;
    list<int> valueList;
    for (auto it : map) {
        key = it.first;
        valueList = it.second;
        for (int value : valueList) {
            procIdxList.push_back(key);
            varIdxList.push_back(value);
            modProcToVarRelMap[key].insert(value);
        }
    }
    modProcToVarPair = make_pair(procIdxList, varIdxList);
    varIdxList.sort();
    varIdxList.unique();
    procIdxList.sort();
    procIdxList.unique();
    modProcToVarMap = map;
    return true;
}

bool ModTableProcToVar::isModifyingAnything(int procIdx) {
    return modProcToVarMap.find(procIdx) != modProcToVarMap.end() && modProcToVarMap[procIdx].size() > 0;
}

list<int> ModTableProcToVar::getProcThatModifies() {
    return procIdxList;
}

pair<list<int>, list<int>> ModTableProcToVar::getProcPair() {
    return modProcToVarPair;
}