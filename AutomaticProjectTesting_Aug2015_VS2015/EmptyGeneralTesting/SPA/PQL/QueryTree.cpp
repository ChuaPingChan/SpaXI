#include "QueryTree.h"

using namespace std;

QueryTree::QueryTree()
{
}

QueryTree::~QueryTree()
{
}

void QueryTree::insertVariable(string type, string var)
{
	if (type == "stmt") 
	{
		stmts.insert(var);
	}

	else if (type == "assign")
	{
		assigns.insert(var);
	}

	else if (type == "while")
	{
		whiles.insert(var);
	}

	else if (type == "variable")
	{
		vars.insert(var);
	}

	else if (type == "constant")
	{
		consts.insert(var);
	}

	else if (type == "prog_line")
	{
		progLines.insert(var);
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

bool QueryTree::varExists(string var)
{
	if (find(stmts.begin(), stmts.end(), var) != stmts.end()) 
	{
		return true;
	}
	else if (find(assigns.begin(), assigns.end(), var) != assigns.end())
	{
		return true;
	}
	else if (find(whiles.begin(), whiles.end(), var) != whiles.end())
	{
		return true;
	}
	else if (find(vars.begin(), vars.end(), var) != vars.end())
	{
		return true;
	}
	else if (find(consts.begin(), consts.end(), var) != consts.end())
	{
		return true;
	}
	else if (find(progLines.begin(), progLines.end(), var) != progLines.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
 