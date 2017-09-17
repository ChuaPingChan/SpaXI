#include "UsesTableStmtToVar.h"

UsesTableStmtToVar::UsesTableStmtToVar() {

}

bool UsesTableStmtToVar::addUsesStmtToVarList(int stmtNumber, string var) 
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (usesStmtToVarMap.find(stmtNumber) == usesStmtToVarMap.end()) {
        usesStmtToVarMap[stmtNumber] = list<string>();
        usesStmtToVarMap[stmtNumber].push_back(var);
        return true;
    }
    else {
        // else, expand the list of variables
        usesStmtToVarMap[stmtNumber].push_back(var);
        return true;
    }
    return false;
}

list<string> UsesTableStmtToVar::getUsesVariablesFromStmt(int stmtNumber) 
{
    return usesStmtToVarMap[stmtNumber];
}

list<int> UsesTableStmtToVar::getStmtThatUses()
{
    unordered_map<int, list<string>>::iterator itr;
    list<int> listOfStmt = list<int>();
    for (itr = usesStmtToVarMap.begin(); itr != usesStmtToVarMap.end(); ++itr)
    {
        listOfStmt.push_back(itr->first);
    }

    return listOfStmt;
}

pair<list<int>, list<string>> UsesTableStmtToVar::getUsesPair()
{
    unordered_map<int, list<string>>::iterator itr;
    pair<list<int>, list<string>> pairOfList;

    for (itr = usesStmtToVarMap.begin(); itr != usesStmtToVarMap.end(); ++itr)
    {
        int stmtNumber = itr->first;
        list<string> usesVarList = itr->second;

        list<string>::iterator listitr;
        for (listitr = usesVarList.begin(); listitr != usesVarList.end(); ++listitr)
        {
            pairOfList.first.push_back(stmtNumber);
            pairOfList.second.push_back(*listitr);
        }
    }
    return pairOfList;
}

bool UsesTableStmtToVar::isUses(int stmtNumber, string var)
{
    return find(usesStmtToVarMap[stmtNumber].begin(), usesStmtToVarMap[stmtNumber].end(), var) != usesStmtToVarMap[stmtNumber].end();
}

bool UsesTableStmtToVar::isUsingAnything(int stmtNumber)
{
    return usesStmtToVarMap.find(stmtNumber) != usesStmtToVarMap.end();
}
