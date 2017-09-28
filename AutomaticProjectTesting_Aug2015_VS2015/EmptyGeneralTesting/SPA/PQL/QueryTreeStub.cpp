#include "QueryTreeStub.h"

using namespace std;

QueryTreeStub::QueryTreeStub()
{
}


QueryTreeStub::~QueryTreeStub()
{
}

void QueryTreeStub::insertVariable(string type, string var)
{
    if (type == "stmt")
    {
        stmts.push_back(var);
    }

    else if (type == "assign")
    {
        assigns.push_back(var);
    }

    else if (type == "while")
    {
        whiles.push_back(var);
    }

    else if (type == "variable")
    {
        vars.push_back(var);
    }

    else if (type == "constant")
    {
        consts.push_back(var);
    }

    else if (type == "prog_line")
    {
        progLines.push_back(var);
    }

    else
    {
        cerr << "Type not recognised!";
    }
}

void QueryTreeStub::insertFollows(array<string, 4> arr)
{
    followsClauses.push_back(arr);
}

void QueryTreeStub::insertFollowsStar(array<string, 4> arr)
{
    followsStarClauses.push_back(arr);
}

void QueryTreeStub::insertParent(array<string, 4> arr)
{
    parentClauses.push_back(arr);
}

void QueryTreeStub::insertParentStar(array<string, 4> arr)
{
    parentStarClauses.push_back(arr);
}

void QueryTreeStub::insertUses(array<string, 4> arr)
{
    usesClauses.push_back(arr);
}

void QueryTreeStub::insertModifies(array<string, 4> arr)
{
    modifiesClauses.push_back(arr);
}

void QueryTreeStub::insertPattern(array<string, 6> arr)
{
    patternClauses.push_back(arr);
}



void QueryTreeStub::insertSelect(array<string, 2> arr)
{
    selectStmt = arr;
}

vector<string> QueryTreeStub::getUnvalidatedStmts()
{
    return unvalidatedStmts;
}

vector<string> QueryTreeStub::getStmts()
{
    return stmts;
}

vector<string> QueryTreeStub::getAssigns()
{
    return assigns;
}

vector<string> QueryTreeStub::getWhiles()
{
    return whiles;
}

vector<string> QueryTreeStub::getVars()
{
    return vars;
}

vector<string> QueryTreeStub::getConsts()
{
    return consts;
}

vector<string> QueryTreeStub::getProgLines()
{
    return progLines;
}

array<string, 2> QueryTreeStub::getSelect()
{
    return selectStmt;
}

vector<array<string, 4>> QueryTreeStub::getFollows()
{
    return followsClauses;
}

vector<array<string, 4>> QueryTreeStub::getFollowsT()
{
    return followsStarClauses;
}

vector<array<string, 4>> QueryTreeStub::getParent()
{
    return parentClauses;
}

vector<array<string, 4>> QueryTreeStub::getParentT()
{
    return parentStarClauses;
}

vector<array<string, 4>> QueryTreeStub::getUses()
{
    return usesClauses;
}

vector<array<string, 4>> QueryTreeStub::getModifies()
{
    return modifiesClauses;
}

vector<array<string, 6>> QueryTreeStub::getPatterns()
{
    return patternClauses;
}

