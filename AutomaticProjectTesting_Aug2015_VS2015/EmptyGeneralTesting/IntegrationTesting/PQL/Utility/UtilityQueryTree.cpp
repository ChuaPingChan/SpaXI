#include "UtilityQueryTree.h"


UtilityQueryTree::UtilityQueryTree()
{
}


UtilityQueryTree::~UtilityQueryTree()
{
}

bool UtilityQueryTree::isGetAllStmtsSame(QueryTreeStub qt1, QueryTreeStub qt2)
{
    vector<string> stmtVectorFromQt1 = qt1.getStmts();
    vector<string> stmtVectorFromQt2 = qt2.getStmts();

    if (stmtVectorFromQt1.size() != stmtVectorFromQt2.size()) {
        return false;
    }

    for (std::vector<string>::iterator itOne = stmtVectorFromQt1.begin(); itOne != stmtVectorFromQt1.end(); ++itOne) {
        string stmtFromQt1 = *itOne;
        if (find(stmtVectorFromQt2.begin(), stmtVectorFromQt2.end(), stmtFromQt1) == stmtVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllAssignsSame(QueryTreeStub qt1, QueryTreeStub qt2)
{
    vector<string> assignVectorFromQt1 = qt1.getAssigns();
    vector<string> assignVectorFromQt2 = qt2.getAssigns();

    if (assignVectorFromQt1.size() != assignVectorFromQt2.size()) {
        return false;
    }

    for (std::vector<string>::iterator itOne = assignVectorFromQt1.begin(); itOne != assignVectorFromQt1.end(); ++itOne) {
        string assignFromQt1 = *itOne;
        if (find(assignVectorFromQt2.begin(), assignVectorFromQt2.end(), assignFromQt1) == assignVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllVariablesSame(QueryTreeStub qt1, QueryTreeStub qt2)
{
    vector<string> variableVectorFromQt1 = qt1.getVars();
    vector<string> variableVectorFromQt2 = qt2.getVars();

    if (variableVectorFromQt1.size() != variableVectorFromQt2.size()) {
        return false;
    }

    for (std::vector<string>::iterator itOne = variableVectorFromQt1.begin(); itOne != variableVectorFromQt1.end(); ++itOne) {
        string variableFromQt1 = *itOne;
        if (find(variableVectorFromQt2.begin(), variableVectorFromQt2.end(), variableFromQt1) == variableVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}

bool UtilityQueryTree::isGetAllWhilesSame(QueryTreeStub qt1, QueryTreeStub qt2)
{
    vector<string> whileVectorFromQt1 = qt1.getWhiles();
    vector<string> whileVectorFromQt2 = qt2.getWhiles();

    if (whileVectorFromQt1.size() != whileVectorFromQt2.size()) {
        return false;
    }

    for (std::vector<string>::iterator itOne = whileVectorFromQt1.begin(); itOne != whileVectorFromQt1.end(); ++itOne) {
        string whileFromQt1 = *itOne;
        if (find(whileVectorFromQt2.begin(), whileVectorFromQt2.end(), whileFromQt1) == whileVectorFromQt2.end()) {
            return false;
        }
    }
    return true;
}
