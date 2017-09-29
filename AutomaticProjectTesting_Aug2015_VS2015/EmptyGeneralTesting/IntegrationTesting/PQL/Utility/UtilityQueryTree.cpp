#include "UtilityQueryTree.h"


UtilityQueryTree::UtilityQueryTree()
{
}


UtilityQueryTree::~UtilityQueryTree()
{
}

bool UtilityQueryTree::isGetAllStmtsSame(QueryTree qt1, QueryTree qt2)
{
    unordered_set<string> stmtVectorFromQt1 = qt1.getStmts();
    unordered_set<string> stmtVectorFromQt2 = qt2.getStmts();

    if (stmtVectorFromQt1.size() != stmtVectorFromQt2.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = stmtVectorFromQt1.begin(); itOne != stmtVectorFromQt1.end(); ++itOne) {
        string stmtFromQt1 = *itOne;
        if (find(stmtVectorFromQt2.begin(), stmtVectorFromQt2.end(), stmtFromQt1) == stmtVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllAssignsSame(QueryTree qt1, QueryTree qt2)
{
    unordered_set<string> assignVectorFromQt1 = qt1.getAssigns();
    unordered_set<string> assignVectorFromQt2 = qt2.getAssigns();

    if (assignVectorFromQt1.size() != assignVectorFromQt2.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = assignVectorFromQt1.begin(); itOne != assignVectorFromQt1.end(); ++itOne) {
        string assignFromQt1 = *itOne;
        if (find(assignVectorFromQt2.begin(), assignVectorFromQt2.end(), assignFromQt1) == assignVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllVariablesSame(QueryTree qt1, QueryTree qt2)
{
    unordered_set<string> variableVectorFromQt1 = qt1.getVars();
    unordered_set<string> variableVectorFromQt2 = qt2.getVars();

    if (variableVectorFromQt1.size() != variableVectorFromQt2.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = variableVectorFromQt1.begin(); itOne != variableVectorFromQt1.end(); ++itOne) {
        string variableFromQt1 = *itOne;
        if (find(variableVectorFromQt2.begin(), variableVectorFromQt2.end(), variableFromQt1) == variableVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllWhilesSame(QueryTree qt1, QueryTree qt2)
{
    unordered_set<string> whileVectorFromQt1 = qt1.getWhiles();
    unordered_set<string> whileVectorFromQt2 = qt2.getWhiles();

    if (whileVectorFromQt1.size() != whileVectorFromQt2.size()) {
        return false;
    }

    for (std::unordered_set<string>::iterator itOne = whileVectorFromQt1.begin(); itOne != whileVectorFromQt1.end(); ++itOne) {
        string whileFromQt1 = *itOne;
        if (find(whileVectorFromQt2.begin(), whileVectorFromQt2.end(), whileFromQt1) == whileVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}
