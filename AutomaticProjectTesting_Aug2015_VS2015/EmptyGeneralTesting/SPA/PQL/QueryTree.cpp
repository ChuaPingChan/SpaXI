#include "QueryTree.h"

using namespace std;

QueryTree::QueryTree()
{
}

QueryTree::~QueryTree()
{
}

void QueryTree::insertVariable(int type, string var)
{
    if (type == STMT) 
    {
        stmts.insert(var);
    }

    else if (type == ASSIGN)
    {
        assigns.insert(var);
    }

    else if (type == WHILE)
    {
        whiles.insert(var);
    }

    /*else if (type == IF)
    {
    ifs.insert(var)
    }*/

    else if (type == PROG_LINE)
    {
        progLines.insert(var);
    }

    /*else if (type == CALL)
    {
        
    }

    else if (type == PROCEDURE)
    {
        procedures.insert(var);
    }*/

    else if (type == VARIABLE)
    {
        vars.insert(var);
    }
   
    else if (type == CONSTANT)
    {
        consts.insert(var);
    }

    else
    {
        cerr << "Type not recognised!";
    }
}

void QueryTree::insertSelect(SelectClause select)
{
    selectStmt = select;
}

void QueryTree::insertSuchThat(SuchThatClause relClause)
{
    suchThatClauses.push_back(relClause);
}

void QueryTree::insertPattern(PatternClause patternClause)
{
    patternClauses.push_back(patternClause);
}

void QueryTree::storeEvaluatorResult(list<string> list)
{
    evaluatorResult = list;
}

unordered_set<string> QueryTree::getStmts()
{
    return stmts;
}

unordered_set<string> QueryTree::getAssigns()
{
    return assigns;
}

unordered_set<string> QueryTree::getWhiles()
{
    return whiles;
}

unordered_set<string> QueryTree::getVars()
{
    return vars;
}

unordered_set<string> QueryTree::getConsts()
{
    return consts;
}

unordered_set<string> QueryTree::getProgLines()
{
    return progLines;
}

SelectClause QueryTree::getSelect()
{
    return selectStmt;
}

vector<SuchThatClause> QueryTree::getSuchThatClauses()
{
    return suchThatClauses;
}

vector<PatternClause> QueryTree::getPatternClauses()
{
    return patternClauses;
}

list<string> QueryTree::getEvaluatorResult()
{
    return evaluatorResult;
}

bool QueryTree::isEntitySynonymExist(string synonym, int entityIdx)
{
    switch (entityIdx) {
        case STMT:
            return (find(stmts.begin(), stmts.end(), synonym) != stmts.end());
        case ASSIGN:
            return (find(assigns.begin(), assigns.end(), synonym) != assigns.end());
        case WHILE:
            return (find(whiles.begin(), whiles.end(), synonym) != whiles.end());
        case IF:
            return false;
        case PROG_LINE:
            return (find(progLines.begin(), progLines.end(), synonym) != progLines.end());
        case CALL:
            return false;
        case PROCEDURE:
            return false;
        case VARIABLE:
            return (find(vars.begin(), vars.end(), synonym) != vars.end());
        case CONSTANT:
            return false;
        case STMTLIST:
            return false;
        default:
            return false;
    }
}
 