#include "UsesTableVar.h"

UsesTableVar::UsesTableVar() {

}

bool UsesTableVar::addUsesVarToStmtList(int varIdx, int stmtNumber) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToStmtMap.find(varIdx) == usesVarToStmtMap.end()) {
        usesVarToStmtMap[varIdx] = list<int>();
        usesVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

bool UsesTableVar::addUsesVarToProcList(int varIdx, int proc)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToProcMap.find(varIdx) == usesVarToProcMap.end()) {
        usesVarToProcMap[varIdx] = list<int>();
        usesVarToProcMap[varIdx].push_back(proc);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToProcMap[varIdx].push_back(proc);
        return true;
    }
    return false;
}

bool UsesTableVar::addUsesVarToAssignList(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToAssignMap.find(varIdx) == usesVarToAssignMap.end()) {
        usesVarToAssignMap[varIdx] = list<int>();
        usesVarToAssignMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToAssignMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

bool UsesTableVar::addUsesVarToWhileStmtList(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToWhileStmtMap.find(varIdx) == usesVarToWhileStmtMap.end()) {
        usesVarToWhileStmtMap[varIdx] = list<int>();
        usesVarToWhileStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToWhileStmtMap[varIdx].push_back(stmtNumber);
		usesVarToWhileStmtMap[varIdx].sort();
		usesVarToWhileStmtMap[varIdx].unique();
        return true;
    }
    return false;
}

bool UsesTableVar::addUsesVarToWhileContainerMap(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToStmtMap.find(varIdx) == usesVarToStmtMap.end()) {
        usesVarToStmtMap[varIdx] = list<int>();
        usesVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

bool UsesTableVar::addUsesVarToIfMap(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToIfMap.find(varIdx) == usesVarToIfMap.end()) {
        usesVarToIfMap[varIdx] = list<int>();
        usesVarToIfMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        usesVarToIfMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

list<int> UsesTableVar::getUsesStmtsFromVar(int varIdx) {
	if (usesVarToStmtMap.find(varIdx) == usesVarToStmtMap.end()) {
		return list<int>();
	}
    return usesVarToStmtMap[varIdx];
}

list<int> UsesTableVar::getUsesProcsFromVar(int varIdx)
{
	if (usesVarToProcMap.find(varIdx) == usesVarToProcMap.end()) {
		return list<int>();
	}
    return usesVarToProcMap[varIdx];
}

list<int> UsesTableVar::getUsesAssignsFromVar(int varIdx)
{
	if (usesVarToAssignMap.find(varIdx) == usesVarToAssignMap.end()) {
		return list<int>();
	}
    return usesVarToAssignMap[varIdx];
}

list<int> UsesTableVar::getUsesWhileStmtFromVar(int varIdx)
{
	if (usesVarToWhileStmtMap.find(varIdx) == usesVarToWhileStmtMap.end()) {
		return list<int>();
	}
    return usesVarToWhileStmtMap[varIdx];
}

list<int> UsesTableVar::getUsesWhileContainersFromVar(int varIdx)
{
	if (usesVarToWhileContainerMap.find(varIdx) == usesVarToWhileContainerMap.end()) {
		return list<int>();
	}
    return usesVarToWhileContainerMap[varIdx];
}

list<int> UsesTableVar::getUsesIfFromVar(int varIdx)
{
	if (usesVarToIfMap.find(varIdx) == usesVarToIfMap.end()) {
		return list<int>();
	}
    return usesVarToIfMap[varIdx];
}

bool UsesTableVar::setStmtMap(unordered_map<int, list<int>> map) {
	usesVarToStmtMap = map;
	return true;
}

bool UsesTableVar::setProcMap(unordered_map<int, list<int>> map) {
	usesVarToProcMap = map;
	return true;
}
