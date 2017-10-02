#include "StmtTypeList.h"

StmtTypeList::StmtTypeList() {

}

bool StmtTypeList::addToAssignStmtList(int stmt) {
    // if stmt number does not exists in assignment list, add to list
    if (find(assignStmtList.begin(), assignStmtList.end(), stmt) == assignStmtList.end()) {
        assignStmtList.push_back(stmt);
        return true;
    }
    return false;
}

bool StmtTypeList::addToWhileStmtList(int stmt) {
    // if stmt number does not exists in assignment list, add to list
    if (find(whileStmtList.begin(), whileStmtList.end(), stmt) == whileStmtList.end()) {
        whileStmtList.push_back(stmt);
        return true;
    }
    return false;
}

list<int> StmtTypeList::getAllStatements() {
	list<int> stmtList;
	stmtList.insert(stmtList.end(), assignStmtList.begin(), assignStmtList.end());
	stmtList.insert(stmtList.end(), whileStmtList.begin(), whileStmtList.end());

	return stmtList;
}

bool StmtTypeList::isAssignStmt(int stmt)
{
    return find(assignStmtList.begin(), assignStmtList.end(), stmt) != assignStmtList.end();
}

bool StmtTypeList::isWhileStmt(int stmt)
{
    return find(whileStmtList.begin(), whileStmtList.end(), stmt) != whileStmtList.end();
}

bool StmtTypeList::isPresent(int stmt)
{
    return stmt <= assignStmtList.size() + whileStmtList.size();
}

list<int> StmtTypeList::getAssignStmtList()
{
    return assignStmtList;
}

list<int> StmtTypeList::getWhileStmtList()
{
    return whileStmtList;
}

/*
    getStmtType: to retrieve the statement numbers according to type
    (e.g. assign, while, ifs)
*/
list<int> StmtTypeList::getStmtType(list<int> stmtList, ENTITY type)
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

pair<list<int>, list<string>> StmtTypeList::getStmtType(pair<list<int>, list<string>> pairOfList, ENTITY type)
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
