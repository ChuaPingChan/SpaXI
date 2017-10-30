#include "UsesTableStmtToVar.h"

UsesTableStmtToVar::UsesTableStmtToVar() {

}

bool UsesTableStmtToVar::addUsesStmtToVarList(int stmtNumber, int varIdx) 
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesStmtToVarMap.find(stmtNumber) == usesStmtToVarMap.end()) {
        usesStmtToVarMap[stmtNumber] = list<int>();
        usesStmtToVarMap[stmtNumber].push_back(varIdx);
        return true;
    }
    else {
        // else, expand the list of variables
        usesStmtToVarMap[stmtNumber].push_back(varIdx);
		usesStmtToVarMap[stmtNumber].sort();
		usesStmtToVarMap[stmtNumber].unique();
        return true;
    }
    return false;
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
    unordered_map<int, list<int>>::iterator itr;
    list<int> listOfStmt = list<int>();
    for (itr = usesStmtToVarMap.begin(); itr != usesStmtToVarMap.end(); ++itr)
    {
		if (itr->second.size() > 0) {
			listOfStmt.push_back(itr->first);
		}
    }

    return listOfStmt;
}

pair<list<int>, list<int>> UsesTableStmtToVar::getUsesPair()
{
    unordered_map<int, list<int>>::iterator itr;
    pair<list<int>, list<int>> pairOfList;

    for (itr = usesStmtToVarMap.begin(); itr != usesStmtToVarMap.end(); ++itr)
    {
        int stmtNumber = itr->first;
        list<int> usesVarList = itr->second;

        list<int>::iterator listitr;
        for (listitr = usesVarList.begin(); listitr != usesVarList.end(); ++listitr)
        {
            pairOfList.first.push_back(stmtNumber);
            pairOfList.second.push_back(*listitr);
        }
    }
    return pairOfList;
}

bool UsesTableStmtToVar::isUses(int stmtNumber, int varIdx)
{
    return find(usesStmtToVarMap[stmtNumber].begin(), usesStmtToVarMap[stmtNumber].end(), varIdx) != usesStmtToVarMap[stmtNumber].end();
}

bool UsesTableStmtToVar::isUsingAnything(int stmtNumber)
{
    return usesStmtToVarMap.find(stmtNumber) != usesStmtToVarMap.end();
}

bool UsesTableStmtToVar::setMap(unordered_map<int, list<int>> map) {
	usesStmtToVarMap = map;
	return true;
}

unordered_map<int, list<int>> UsesTableStmtToVar::getMap() {
	return usesStmtToVarMap;
}