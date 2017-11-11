#include "UsesTableProcToVar.h"

UsesTableProcToVar::UsesTableProcToVar() {

}

/*
Populate the respective PKB relationship
*/
bool UsesTableProcToVar::addUsesProcToVarList(int procIdx, int varIdx) {
    usesProcToVarMap[procIdx].push_back(varIdx);
    usesProcToVarMap[procIdx].sort();
    usesProcToVarMap[procIdx].unique();
    usesProcToVarRelMap[procIdx].insert(varIdx);
    return true;
}

list<int> UsesTableProcToVar::getUsesVariablesFromProc(int procIdx) {
    if (usesProcToVarMap.find(procIdx) == usesProcToVarMap.end()) {
        return list<int>();
    }

    return usesProcToVarMap[procIdx];
}

/*
Iterate through the new map and populate the relations if necessary
*/
bool UsesTableProcToVar::setMap(unordered_map<int, list<int>> targetMap) {
    int key;
    list<int> valueList;
    for (auto it : targetMap) {
        key = it.first;
        valueList = it.second;
        for (int value : valueList) {
            procIdxList.push_back(key);
            varIdxList.push_back(value);
            usesProcToVarRelMap[key].insert(value);
        }
    }
    usesProcToVarPair = make_pair(procIdxList, varIdxList);
    varIdxList.sort();
    varIdxList.unique();
    procIdxList.sort();
    procIdxList.unique();
    usesProcToVarMap = targetMap;
    return true;
}

unordered_map<int, list<int>> UsesTableProcToVar::getMap() {
    return usesProcToVarMap;
}

/*
Check if procedure uses
*/
bool UsesTableProcToVar::isUses(int procIdx, int varIdx) {
    if (usesProcToVarRelMap.find(procIdx) != usesProcToVarRelMap.end()) {
        return usesProcToVarRelMap[procIdx].find(varIdx) != usesProcToVarRelMap[procIdx].end();
    }
    return false;
}

bool UsesTableProcToVar::isUsingAnything(int procIdx) {
    return usesProcToVarMap.find(procIdx) != usesProcToVarMap.end() && usesProcToVarMap[procIdx].size() > 0;
}

list<int> UsesTableProcToVar::getProcThatUses() {
    return procIdxList;
}

pair<list<int>, list<int>> UsesTableProcToVar::getProcPair() {
    return usesProcToVarPair;
}