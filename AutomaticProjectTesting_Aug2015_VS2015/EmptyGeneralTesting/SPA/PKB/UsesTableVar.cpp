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

bool UsesTableVar::addUsesVarToProcList(int varIdx, string proc)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesVarToProcMap.find(varIdx) == usesVarToProcMap.end()) {
        usesVarToProcMap[varIdx] = list<string>();
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

list<int> UsesTableVar::getUsesStmtsFromVar(int varIdx) {
    return usesVarToStmtMap[varIdx];
}

list<string> UsesTableVar::getUsesProcsFromVar(int varIdx)
{
    return usesVarToProcMap[varIdx];
}

list<int> UsesTableVar::getUsesAssignsFromVar(int varIdx)
{
    return usesVarToAssignMap[varIdx];
}

list<int> UsesTableVar::getUsesWhileStmtFromVar(int varIdx)
{
    return usesVarToWhileStmtMap[varIdx];
}

list<int> UsesTableVar::getUsesWhileContainersFromVar(int varIdx)
{
    return usesVarToWhileContainerMap[varIdx];
}
