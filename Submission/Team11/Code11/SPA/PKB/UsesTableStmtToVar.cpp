#include "UsesTableStmtToVar.h"

UsesTableStmtToVar::UsesTableStmtToVar() {

}

/*
Populate the required data structure
*/
bool UsesTableStmtToVar::addUsesStmtToVarList(int stmtNumber, int varIdx)
{
    usesStmtToVarMap[stmtNumber].push_back(varIdx);
    usesStmtToVarMap[stmtNumber].sort();
    usesStmtToVarMap[stmtNumber].unique();
    usesStmtToVarRelMap[stmtNumber].insert(varIdx);
    return true;
}

list<int> UsesTableStmtToVar::getUsesVariablesFromStmt(int stmtNumber)
{
    if (usesStmtToVarMap.find(stmtNumber) == usesStmtToVarMap.end()) {
        return list<int>();
    }

    return usesStmtToVarMap[stmtNumber];
}

list<int> UsesTableStmtToVar::getStmtThatUses()
{
    return usesStmtList;
}

pair<list<int>, list<int>> UsesTableStmtToVar::getUsesPair()
{
    return usesStmtToVarPair;
}

bool UsesTableStmtToVar::isUses(int stmtNumber, int varIdx)
{
    if (usesStmtToVarRelMap.find(stmtNumber) != usesStmtToVarRelMap.end()) {
        return usesStmtToVarRelMap[stmtNumber].find(varIdx) != usesStmtToVarRelMap[stmtNumber].end();
    }
    return false;
}

bool UsesTableStmtToVar::isUsingAnything(int stmtNumber)
{
    return usesStmtToVarMap.find(stmtNumber) != usesStmtToVarMap.end();
}

/*
This method iterates through the new map and resets the tables
*/
bool UsesTableStmtToVar::setMap(unordered_map<int, list<int>> map) {
    int key;
    list<int> valueList;
    for (auto it : map) {
        key = it.first;
        valueList = it.second;
        for (int value : valueList) {
            usesStmtList.push_back(key);
            usesVarList.push_back(value);
            usesStmtToVarRelMap[key].insert(value);
        }
    }
    usesStmtToVarPair = make_pair(usesStmtList, usesVarList);
    usesStmtList.sort();
    usesStmtList.unique();
    usesVarList.sort();
    usesVarList.unique();
    usesStmtToVarMap = map;
    return true;
}

unordered_map<int, list<int>> UsesTableStmtToVar::getMap() {
    return usesStmtToVarMap;
}