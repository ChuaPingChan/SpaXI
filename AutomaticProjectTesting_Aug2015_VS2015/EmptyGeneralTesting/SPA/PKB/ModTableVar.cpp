#include "ModTableVar.h"

using namespace std;

ModTableVar::ModTableVar() {

}

bool ModTableVar::addModVarToStmtList(int varIdx, int stmtNumber) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToStmtMap.find(varIdx) == modVarToStmtMap.end()) {
        modVarToStmtMap[varIdx] = list<int>();
        modVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToStmtMap[varIdx].push_back(stmtNumber);
		modVarToStmtMap[varIdx].sort();
        modVarToStmtMap[varIdx].unique();
        return true;
    }
    return false;
}

bool ModTableVar::addModVarToProcList(int varIdx, int proc)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToProcMap.find(varIdx) == modVarToProcMap.end()) {
        modVarToProcMap[varIdx] = list<int>();
        modVarToProcMap[varIdx].push_back(proc);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToProcMap[varIdx].push_back(proc);
        return true;
    }
    return false;
}

bool ModTableVar::addModVarToAssignList(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToAssignMap.find(varIdx) == modVarToAssignMap.end()) {
        modVarToAssignMap[varIdx] = list<int>();
        modVarToAssignMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToAssignMap[varIdx].push_back(stmtNumber);
		modVarToAssignMap[varIdx].sort();
		modVarToAssignMap[varIdx].unique();
        return true;
    }
    return false;
}

bool ModTableVar::addModVarToWhileStmtList(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToWhileStmtMap.find(varIdx) == modVarToWhileStmtMap.end()) {
        modVarToWhileStmtMap[varIdx] = list<int>();
        modVarToWhileStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToWhileStmtMap[varIdx].push_back(stmtNumber);
		modVarToWhileStmtMap[varIdx].sort();
		modVarToWhileStmtMap[varIdx].unique();
        return true;
    }
    return false;
}

bool ModTableVar::addModVarToWhileContainerMap(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToStmtMap.find(varIdx) == modVarToStmtMap.end()) {
        modVarToStmtMap[varIdx] = list<int>();
        modVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToStmtMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

bool ModTableVar::addModVarToIfMap(int varIdx, int stmtNumber)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToIfMap.find(varIdx) == modVarToIfMap.end()) {
        modVarToIfMap[varIdx] = list<int>();
        modVarToIfMap[varIdx].push_back(stmtNumber);
        return true;
    }
    else {
        // else, expand the list of variables
        modVarToIfMap[varIdx].push_back(stmtNumber);
        return true;
    }
    return false;
}

list<int> ModTableVar::getModStmtsFromVar(int varIdx) {
	if (modVarToStmtMap.find(varIdx) == modVarToStmtMap.end()) {
		return list<int>();
	}

    return modVarToStmtMap[varIdx];
}

list<int> ModTableVar::getModProcsFromVar(int varIdx)
{
	if (modVarToProcMap.find(varIdx) == modVarToStmtMap.end()) {
		return list<int>();
	}
    return modVarToProcMap[varIdx];
}

list<int> ModTableVar::getModAssignsFromVar(int varIdx)
{
	if (modVarToAssignMap.find(varIdx) == modVarToAssignMap.end()) {
		return list<int>();
	}
    return modVarToAssignMap[varIdx];
}

list<int> ModTableVar::getModWhileStmtFromVar(int varIdx)
{
	if (modVarToWhileStmtMap.find(varIdx) == modVarToWhileStmtMap.end()) {
		return list<int>();
	}
    return modVarToWhileStmtMap[varIdx];
}

list<int> ModTableVar::getModWhileContainersFromVar(int varIdx)
{
	if (modVarToWhileContainerMap.find(varIdx) == modVarToWhileContainerMap.end()) {
		return list<int>();
	}
    return modVarToWhileContainerMap[varIdx];
}

list<int> ModTableVar::getModIfFromVar(int varIdx)
{
	if (modVarToIfMap.find(varIdx) == modVarToIfMap.end()) {
		return list<int>();
	}
    return modVarToIfMap[varIdx];
}

bool ModTableVar::setStmtMap(unordered_map<int, list<int>> map) {
	modVarToStmtMap = map;
	return true;
}

bool ModTableVar::setProcMap(unordered_map<int, list<int>> map) {
	modVarToProcMap = map;
	return true;
}