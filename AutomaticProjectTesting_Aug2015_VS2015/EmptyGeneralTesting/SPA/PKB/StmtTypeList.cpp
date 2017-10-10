#include "StmtTypeList.h"

StmtTypeList::StmtTypeList() {

}

bool StmtTypeList::addToAssignStmtList(int stmt) {
    // if stmt number does not exists in assignment list, add to list
    if (find(assignStmtList.begin(), assignStmtList.end(), stmt) == assignStmtList.end()) {
        assignStmtList.push_back(stmt);
		allStmtList.push_back(stmt);
        return true;
    }
    return false;
}

bool StmtTypeList::addToWhileStmtList(int stmt) {
    // if stmt number does not exists in assignment list, add to list
    if (find(whileStmtList.begin(), whileStmtList.end(), stmt) == whileStmtList.end()) {
        whileStmtList.push_back(stmt);
		allStmtList.push_back(stmt);
        return true;
    }
    return false;
}

bool StmtTypeList::addToCallsStmtList(int stmt) {
	if (find(callsStmtList.begin(), callsStmtList.end(), stmt) == callsStmtList.end()) {
		callsStmtList.push_back(stmt);
		allStmtList.push_back(stmt);
		return true;
	}
	return false;
}

bool StmtTypeList::addToIfStmtList(int stmt)
{
    if (find(ifStmtList.begin(), ifStmtList.end(), stmt) == ifStmtList.end()) {
        ifStmtList.push_back(stmt);
        allStmtList.push_back(stmt);
        return true;
    }
    return false;
}

list<int> StmtTypeList::getAllStatements() {
	return allStmtList;
}

bool StmtTypeList::isAssignStmt(int stmt)
{
    return find(assignStmtList.begin(), assignStmtList.end(), stmt) != assignStmtList.end();
}

bool StmtTypeList::isWhileStmt(int stmt)
{
    return find(whileStmtList.begin(), whileStmtList.end(), stmt) != whileStmtList.end();
}

bool StmtTypeList::isCallsStmt(int stmt)
{
	return find(callsStmtList.begin(), callsStmtList.end(), stmt) != callsStmtList.end();
}

bool StmtTypeList::isPresent(int stmt)
{
    return stmt <= assignStmtList.size() + whileStmtList.size() + callsStmtList.size() + ifStmtList.size();
}

bool StmtTypeList::isIfStmt(int stmt)
{
    return find(ifStmtList.begin(), ifStmtList.end(), stmt) != ifStmtList.end();;
}

list<int> StmtTypeList::getAssignStmtList()
{
    return assignStmtList;
}

list<int> StmtTypeList::getWhileStmtList()
{
    return whileStmtList;
}

list<int> StmtTypeList::getIfStmtList()
{
    return ifStmtList;
}

list<int> StmtTypeList::getCallsStmtList()
{
	return callsStmtList;
}

/*
    getStmtType: to retrieve the statement numbers according to type
    (e.g. assign, while, ifs)
*/
//TODO 1 change PKB entity types to use this method
list<int> StmtTypeList::getStmtType(list<int> stmtList, Entity type)
{
    list<int> filteredList;
    list<int>::iterator it;
    for (it = stmtList.begin(); it != stmtList.end(); ++it)
    {
        if (type == ASSIGN)
        {
            if (isAssignStmt(*it))
            {
                filteredList.push_back(*it);
            }
        }
        else if (type == WHILE)
        {
            if (isWhileStmt(*it))
            {
                filteredList.push_back(*it);
            }
        }
        else if (type == STMT)
        {
            filteredList.push_back(*it);
        }
    }
    return filteredList;
}

pair<list<int>, list<string>> StmtTypeList::getStmtType(pair<list<int>, list<string>> pairOfList, Entity type)
{
    list<int> stmts = pairOfList.first;
    list<string> vars = pairOfList.second;
    list<pair<int, string>> listOfPairs;
    // converting from pair of two lists into list of pairs
    while (!stmts.empty() && !vars.empty())
    {
        listOfPairs.push_back(make_pair(stmts.front(), vars.front()));
        stmts.pop_front();
        vars.pop_back();
    }
    // filtering away unwanted pairs
    list<pair<int, string>> filteredListOfPairs;
    list<pair<int, string>>::iterator it;
    for (it = listOfPairs.begin(); it != listOfPairs.end(); ++it)
    {
        if (type == ASSIGN)
        {
            if (isAssignStmt(it->first))
            {
                filteredListOfPairs.push_back(*it);
            }
        }
        else if (type == WHILE)
        {
            if (isWhileStmt(it->first))
            {
                filteredListOfPairs.push_back(*it);
            }
        }
        else if (type == STMT)
        {
            filteredListOfPairs.push_back(*it);
        }
		//TODO 1 add if
    }
    // convert back to pair of lists
    list<int> resultStmts;
    list<string> resultVars;
    list<pair<int, string>>::iterator resultItr;
    for (resultItr = filteredListOfPairs.begin();
        resultItr != filteredListOfPairs.end(); ++resultItr)
    {
        resultStmts.push_back(resultItr->first);
        resultVars.push_back(resultItr->second);
    }
    
    return make_pair(resultStmts, resultVars);
}
