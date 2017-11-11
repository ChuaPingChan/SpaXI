#include "ModTableStmtToVar.h"

using namespace std;

ModTableStmtToVar::ModTableStmtToVar() {

}

/*
This method adds the relation to the modifies table
*/
bool ModTableStmtToVar::addModStmtToVarList(int stmtNumber, int varIdx) {
    modStmtToVarMap[stmtNumber].push_back(varIdx);
    modStmtToVarMap[stmtNumber].sort();
    modStmtToVarMap[stmtNumber].unique();
    modStmtToVarRelMap[stmtNumber].insert(varIdx);
    return true;
}

list<int> ModTableStmtToVar::getModVariablesFromStmt(int stmtNumber)
{
    if (modStmtToVarMap.find(stmtNumber) == modStmtToVarMap.end()) {
        return list<int>();
    }

    return modStmtToVarMap[stmtNumber];
}

list<int> ModTableStmtToVar::getStmtThatModifies()
{
    return modStmtList;
}

pair<list<int>, list<int>> ModTableStmtToVar::getModPair()
{
    return modStmtToVarPair;
}

bool ModTableStmtToVar::isMod(int stmtNumber, int varIdx)
{
    if (modStmtToVarRelMap.find(stmtNumber) != modStmtToVarRelMap.end()) {
        return modStmtToVarRelMap[stmtNumber].find(varIdx) != modStmtToVarRelMap[stmtNumber].end();
    }
    return false;
}

bool ModTableStmtToVar::isModifyingAnything(int stmtNumber)
{
    return modStmtToVarMap.find(stmtNumber) != modStmtToVarMap.end();
}

/*
This method iterates through each value of the map and
populate the modifies table respectively
*/
bool ModTableStmtToVar::setMap(unordered_map<int, list<int>> map) {
    int key;
    list<int> valueList;
    for (auto it : map) {
        key = it.first;
        valueList = it.second;
        for (int value : valueList) {
            modStmtList.push_back(key);
            modVarList.push_back(value);
            modStmtToVarRelMap[key].insert(value);
        }
    }
    modStmtToVarPair = make_pair(modStmtList, modVarList);
    modStmtList.sort();
    modStmtList.unique();
    modVarList.sort();
    modVarList.unique();
    modStmtToVarMap = map;
    return true;
}

unordered_map<int, list<int>> ModTableStmtToVar::getMap() {
    return modStmtToVarMap;
}