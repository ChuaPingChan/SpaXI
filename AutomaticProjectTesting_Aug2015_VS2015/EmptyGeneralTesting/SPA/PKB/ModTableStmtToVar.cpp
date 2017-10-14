#include "ModTableStmtToVar.h"

using namespace std;

ModTableStmtToVar::ModTableStmtToVar() {

}

bool ModTableStmtToVar::addModStmtToVarList(int stmtNumber, int varIdx) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modStmtToVarMap.find(stmtNumber) == modStmtToVarMap.end()) {
        modStmtToVarMap[stmtNumber] = list<int>();
        modStmtToVarMap[stmtNumber].push_back(varIdx);
        return true;
    }
    else {
        // else, expand the list of variables
        modStmtToVarMap[stmtNumber].push_back(varIdx);
		modStmtToVarMap[stmtNumber].sort();
        modStmtToVarMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<int> ModTableStmtToVar::getModVariablesFromStmt(int stmtNumber) 
{
    return modStmtToVarMap[stmtNumber];
}

list<int> ModTableStmtToVar::getStmtThatModifies()
{
    unordered_map<int, list<int>>::iterator itr;
    list<int> listOfStmt;
    for (itr = modStmtToVarMap.begin(); itr != modStmtToVarMap.end(); ++itr) 
    {
        listOfStmt.push_back(itr->first);
    }

    return listOfStmt;
}

pair<list<int>,list<int>> ModTableStmtToVar::getModPair()
{
    unordered_map<int, list<int>>::iterator itr;
    pair<list<int>,list<int>> pairOfList;
  
    for (itr = modStmtToVarMap.begin(); itr != modStmtToVarMap.end(); ++itr)
    {
        int stmtNumber = itr->first;
        list<int> modVarList = itr->second;

        list<int>::iterator listitr;
        for (listitr = modVarList.begin(); listitr != modVarList.end(); ++listitr)
        {
            pairOfList.first.push_back(stmtNumber);
            pairOfList.second.push_back(*listitr);
        }
    }
    return pairOfList;
}

bool ModTableStmtToVar::isMod(int stmtNumber, int varIdx)
{
    return find(modStmtToVarMap[stmtNumber].begin(),modStmtToVarMap[stmtNumber].end(),varIdx) != modStmtToVarMap[stmtNumber].end();
}

bool ModTableStmtToVar::isModifyingAnything(int stmtNumber)
{
    return modStmtToVarMap.find(stmtNumber) != modStmtToVarMap.end();
}

bool ModTableStmtToVar::setMap(unordered_map<int, list<int>> map) {
	modStmtToVarMap = map;
	return true;
}

unordered_map<int, list<int>> ModTableStmtToVar::getMap() {
	return modStmtToVarMap;
}