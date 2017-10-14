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
        else if (type == IF)
        {
            if (isIfStmt(*it))
            {
                filteredList.push_back(*it);
            }
        }
        else
        {
            filteredList.push_back(*it);
        }
    }
    return filteredList;
}

pair<list<int>, list<int>> StmtTypeList::getStmtType(pair<list<int>, list<int>> pairOfList, Entity type)
{
    list<int> stmts = pairOfList.first;
    list<int> vars = pairOfList.second;
    // converting from pair of two lists into list of pairs
	pair<list<int>, list<int>> resultPair;
	resultPair = make_pair(list<int>(), list<int>());
	int currStmt;
	int currVar;

    while (!stmts.empty() && !vars.empty())
    {
		currStmt = stmts.front();
		stmts.pop_front();
		currVar = vars.front();
		vars.pop_front();

		if (type == ASSIGN) {
			if (isAssignStmt(currStmt)) {
				resultPair.first.push_back(currStmt);
				resultPair.second.push_back(currVar);
			}
		}

		else if (type == WHILE) {
			if (isWhileStmt(currStmt)) {
				resultPair.first.push_back(currStmt);
				resultPair.second.push_back(currVar);
			}

		}
		/* TODO 1 uncomment if
		else if (type == IF) {
			if (isIfStmt(currStmt)) {
				resultPair.first.push_back(currStmt);
				resultPair.second.push_back(currVar);
			}

		}*/

		else if (type == CALL) {
			if (isCallsStmt(currStmt)) {
				resultPair.first.push_back(currStmt);
				resultPair.second.push_back(currVar);
			}

		}

		else {
			resultPair = pairOfList;
			break;
		}
    }

	return resultPair;
}
