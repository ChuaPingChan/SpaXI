#include "UtilityQueryTree.h"


UtilityQueryTree::UtilityQueryTree()
{
}


UtilityQueryTree::~UtilityQueryTree()
{
}

bool UtilityQueryTree::isSameSelectionType(SelectionType expectedType, QueryTree qt)
{
    SelectClause sc = qt.getSelectClause();
    SelectionType actualType = sc.getSelectionType();
    return expectedType == actualType;
}

bool UtilityQueryTree::isSameContentAllStmts(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> stmtVectorFromQt = qt.getStmts();

    if (stmtVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedstmt = *itOne;
        if (find(stmtVectorFromQt.begin(), stmtVectorFromQt.end(), expectedstmt) == stmtVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllAssigns(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> assignVectorFromQt = qt.getAssigns();

    if (assignVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedassign = *itOne;
        if (find(assignVectorFromQt.begin(), assignVectorFromQt.end(), expectedassign) == assignVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllWhiles(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> whileVectorFromQt = qt.getWhiles();

    if (whileVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedwhile = *itOne;
        if (find(whileVectorFromQt.begin(), whileVectorFromQt.end(), expectedwhile) == whileVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllIfs(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> ifVectorFromQt = qt.getIfs();

    if (ifVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedif = *itOne;
        if (find(ifVectorFromQt.begin(), ifVectorFromQt.end(), expectedif) == ifVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllProgLines(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> progLineVectorFromQt = qt.getProgLines();

    if (progLineVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedprogLine = *itOne;
        if (find(progLineVectorFromQt.begin(), progLineVectorFromQt.end(), expectedprogLine) == progLineVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllCalls(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> callVectorFromQt = qt.getCalls();

    if (callVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedcall = *itOne;
        if (find(callVectorFromQt.begin(), callVectorFromQt.end(), expectedcall) == callVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllProcedures(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> procedureVectorFromQt = qt.getProcedures();

    if (procedureVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedprocedure = *itOne;
        if (find(procedureVectorFromQt.begin(), procedureVectorFromQt.end(), expectedprocedure) == procedureVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isSameContentAllVariables(unordered_set<string> expectedList, QueryTree qt)
{
    unordered_set<string> variableVectorFromQt = qt.getVars();

    if (variableVectorFromQt.size() != expectedList.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = expectedList.begin(); itOne != expectedList.end(); ++itOne) {
        string expectedvariable = *itOne;
        if (find(variableVectorFromQt.begin(), variableVectorFromQt.end(), expectedvariable) == variableVectorFromQt.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isEmptyWithClauseVectorInTree(QueryTree qt)
{
    return qt.getWithClauses().empty();
}
