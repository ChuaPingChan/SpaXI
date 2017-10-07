#include "QueryTree.h"

using namespace std;

QueryTree::QueryTree()
{
}

QueryTree::~QueryTree()
{
}

void QueryTree::insertSynonym(int type, string synonym)
{
    if (type == STMT) 
    {
        _stmts.insert(synonym);
    }

    else if (type == ASSIGN)
    {
        _assigns.insert(synonym);
    }

    else if (type == WHILE)
    {
        _whiles.insert(synonym);
    }

    else if (type == IF)
    {
        _ifs.insert(synonym);
    }

    else if (type == PROG_LINE)
    {
        _progLines.insert(synonym);
    }

    else if (type == CALL)
    {
        _calls.insert(synonym);
    }

    else if (type == PROCEDURE)
    {
        _procedures.insert(synonym);
    }

    else if (type == VARIABLE)
    {
        _vars.insert(synonym);
    }
   
    else if (type == CONSTANT)
    {
        _consts.insert(synonym);
    }

    else
    {
        cerr << "Type not recognised!";
    }
}

void QueryTree::insertSelect(SelectClause select)
{
    _selectStmt = select;
}

void QueryTree::insertSuchThat(SuchThatClause relClause)
{
    _suchThatClauses.push_back(relClause);
}

void QueryTree::insertPattern(PatternClause patternClause)
{
    _patternClauses.push_back(patternClause);
}

void QueryTree::storeEvaluatorResult(ClauseResult result)
{
    _evaluatorResult = result;
}

unordered_set<string> QueryTree::getStmts()
{
    return _stmts;
}

unordered_set<string> QueryTree::getAssigns()
{
    return _assigns;
}

unordered_set<string> QueryTree::getWhiles()
{
    return _whiles;
}

unordered_set<string> QueryTree::getIfs()
{
    return _ifs;
}

unordered_set<string> QueryTree::getCalls()
{
    return _calls;
}

unordered_set<string> QueryTree::getProcedures()
{
    return _procedures;
}

unordered_set<string> QueryTree::getVars()
{
    return _vars;
}

unordered_set<string> QueryTree::getConsts()
{
    return _consts;
}

unordered_set<string> QueryTree::getProgLines()
{
    return _progLines;
}

SelectClause QueryTree::getSelect()
{
    return _selectStmt;
}

vector<SuchThatClause> QueryTree::getSuchThatClauses()
{
    return _suchThatClauses;
}

vector<PatternClause> QueryTree::getPatternClauses()
{
    return _patternClauses;
}

ClauseResult QueryTree::getEvaluatorResult()
{
    return _evaluatorResult;
}

bool QueryTree::isEntitySynonymExist(string synonym, Entity entityIdx)
{
    switch (entityIdx) {
        case STMT:
            return (find(_stmts.begin(), _stmts.end(), synonym) != _stmts.end());
        case ASSIGN:
            return (find(_assigns.begin(), _assigns.end(), synonym) != _assigns.end());
        case WHILE:
            return (find(_whiles.begin(), _whiles.end(), synonym) != _whiles.end());
        case IF:
            return false;
        case PROG_LINE:
            return (find(_progLines.begin(), _progLines.end(), synonym) != _progLines.end());
        case CALL:
            return false;
        case PROCEDURE:
            return false;
        case VARIABLE:
            return (find(_vars.begin(), _vars.end(), synonym) != _vars.end());
        case CONSTANT:
            return false;
        case STMTLIST:
            return false;
        default:
            return false;
    }
}
 