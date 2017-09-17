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

bool ModTableVar::addModVarToProcList(int varIdx, string proc)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modVarToProcMap.find(varIdx) == modVarToProcMap.end()) {
        modVarToProcMap[varIdx] = list<string>();
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

list<int> ModTableVar::getModStmtsFromVar(int varIdx) {
    return modVarToStmtMap[varIdx];
}

list<string> ModTableVar::getModProcsFromVar(int varIdx)
{
    return modVarToProcMap[varIdx];
}

list<int> ModTableVar::getModAssignsFromVar(int varIdx)
{
    return modVarToAssignMap[varIdx];
}

list<int> ModTableVar::getModWhileStmtFromVar(int varIdx)
{
    return modVarToWhileStmtMap[varIdx];
}

list<int> ModTableVar::getModWhileContainersFromVar(int varIdx)
{
    return modVarToWhileContainerMap[varIdx];
}
