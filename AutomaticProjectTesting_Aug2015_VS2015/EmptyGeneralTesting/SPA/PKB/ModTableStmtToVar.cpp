#include "ModTableStmtToVar.h"

using namespace std;

ModTableStmtToVar::ModTableStmtToVar() {

}

bool ModTableStmtToVar::addModStmtToVarList(int stmtNumber, string var) {
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (modStmtToVarMap.find(stmtNumber) == modStmtToVarMap.end()) {
        modStmtToVarMap[stmtNumber] = list<string>();
        modStmtToVarMap[stmtNumber].push_back(var);
        modStmtToVarMap[stmtNumber].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        modStmtToVarMap[stmtNumber].push_back(var);
        modStmtToVarMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<string> ModTableStmtToVar::getModVariablesFromStmt(int stmtNumber) 
{
    return modStmtToVarMap[stmtNumber];
}

list<int> ModTableStmtToVar::getStmtThatModifies()
{
    unordered_map<int, list<string>>::iterator itr;
    list<int> listOfStmt;
    for (itr = modStmtToVarMap.begin(); itr != modStmtToVarMap.end(); ++itr) 
    {
        listOfStmt.push_back(itr->first);
    }

    return listOfStmt;
}

pair<list<int>,list<string>> ModTableStmtToVar::getModPair()
{
    unordered_map<int, list<string>>::iterator itr;
    pair<list<int>,list<string>> pairOfList;
    
    for (itr = modStmtToVarMap.begin(); itr != modStmtToVarMap.end(); ++itr)
    {
        int stmtNumber = itr->first;
        list<string> modVarList = itr->second;

        list<string>::iterator listitr;
        for (listitr = modVarList.begin(); listitr != modVarList.end(); ++listitr)
        {
            pairOfList.first.push_back(stmtNumber);
            pairOfList.second.push_back(*listitr);
        }
    }
    return pairOfList;
}

bool ModTableStmtToVar::isMod(int stmtNumber, string var)
{
    return find(modStmtToVarMap[stmtNumber].begin(),modStmtToVarMap[stmtNumber].end(),var) != modStmtToVarMap[stmtNumber].end();
}

bool ModTableStmtToVar::isModifyingAnything(int stmtNumber)
{
    return modStmtToVarMap.find(stmtNumber) != modStmtToVarMap.end();
}

