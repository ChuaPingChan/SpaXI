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

bool StmtTypeList::addToCallsStmtList(int stmt, int calleeProcIdx, string calleeProcName) {
	if (find(callsStmtList.begin(), callsStmtList.end(), stmt) == callsStmtList.end()) {
		callsStmtList.push_back(stmt);
		allStmtList.push_back(stmt);
		allCalleeName.push_back(calleeProcName);
		callToProcNameMap[stmt] = calleeProcName;
		procNameToCallMap[calleeProcName].push_back(stmt);
		procNameToCallMap[calleeProcName].sort();
		procNameToCallMap[calleeProcName].unique();
		callToProcIdxMap[stmt] = calleeProcIdx;
		return true;
	}
	return false;
}

list<int> StmtTypeList::getStmtFromCalleeProcName(string calleeProcName) {
	if (procNameToCallMap.find(calleeProcName) == procNameToCallMap.end()) {
		return list<int>();
	}

	return procNameToCallMap[calleeProcName];
}

int StmtTypeList::getProcIdxFromCall(int stmt) {
	if (callToProcIdxMap.find(stmt) == callToProcIdxMap.end()) {
		return -1;
	}

	return callToProcIdxMap[stmt];
}

list<string> StmtTypeList::getAllCalleeNames() {
	return allCalleeName;
}

unordered_map<int, int> StmtTypeList::getCallToProcIdxMap() {
	return callToProcIdxMap;
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

bool StmtTypeList::isStatement(int stmt) {
	return find(allStmtList.begin(), allStmtList.end(), stmt) != allStmtList.end();
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
		else if (type == CALL) {
			if (isCallsStmt(*it))
			{
				filteredList.push_back(*it);
			}
		}
		else if (type == STMT) {
			return stmtList;
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

		else if (type == IF) {
			if (isIfStmt(currStmt)) {
				resultPair.first.push_back(currStmt);
				resultPair.second.push_back(currVar);
			}

		}

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

pair<list<int>, list<int>> StmtTypeList::getStmtType(pair<list<int>, list<int>> pairOfList, Entity type1, Entity type2) {
	//process first entity
	pair<list<int>, list<int>> firstResultPair = getStmtType(pairOfList, type1);
	firstResultPair = make_pair(firstResultPair.second, firstResultPair.first);
	pair<list<int>, list<int>> secondResultPair = getStmtType(firstResultPair, type2);
	secondResultPair = make_pair(secondResultPair.second, secondResultPair.first);

	return secondResultPair;
}

list<int> StmtTypeList::getStmtType(int stmt, Entity type) {
	list<int> resultList;
	if (type == ASSIGN)
	{
		if (isAssignStmt(stmt))
		{
			resultList.push_back(stmt);
		}
	}
	
	else if (type == WHILE)
	{
		if (isWhileStmt(stmt))
		{
			resultList.push_back(stmt);
		}
	}

	else if (type == IF)
	{
		if (isIfStmt(stmt))
		{
			resultList.push_back(stmt);
		}
	}

	else if (type == CALL)
	{
		if (isCallsStmt(stmt))
		{
			resultList.push_back(stmt);
		}
	}

	else
	{
		resultList.push_back(stmt);
	}

	return resultList;
}