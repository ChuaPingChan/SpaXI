#include "QueryTree.h"
#include <iostream>


QueryTree::QueryTree()
{
	init();
}


QueryTree::~QueryTree()
{
}

void QueryTree::init()
{
	setInited(true);
	setSplitted(false);
	setValidated(false);
	setEvaluated(false);
}

void QueryTree::storeUnvalidatedStmts(vector<string> splittedVec)
{
	unvalidatedStmts = splittedVec;
	setSplitted(true);
}

void QueryTree::insertVariable(string type, string var)
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

	this->numVar++;
}

void QueryTree::insertSuchThat(string clause)
{
	suchThatClauses.push_back(clause);
}

void QueryTree::insertSelect(string stmt)
{
	selectStmt = stmt;
}

void QueryTree::insertPattern(string pattern)
{
	patternStmt = pattern;
}

vector<string> QueryTree::getUnvalidatedStmts()
{
	return unvalidatedStmts;
}

vector<string> QueryTree::getStmts()
{
	return stmts;
}

vector<string> QueryTree::getAssigns()
{
	return assigns;
}

vector<string> QueryTree::getWhiles()
{
	return whiles;
}

vector<string> QueryTree::getVars()
{
	return vars;
}

vector<string> QueryTree::getConsts()
{
	return consts;
}

vector<string> QueryTree::getProgLines()
{
	return progLines;
}

int QueryTree::getNumVar()
{
	return numVar;
}

int QueryTree::getNumSuchThat()
{
	return suchThatClauses.size();
}

bool QueryTree::isInit()
{
	return inited;
}

bool QueryTree::isSplitted()
{
	return splitted;
}

bool QueryTree::isValidated()
{
	return validated;
}

bool QueryTree::isEvaluated()
{
	return evaluated;
}

void QueryTree::setValidatedTrue()
{
	setValidated(true);
}

void QueryTree::setEvaluatedTrue()
{
	setEvaluated(true);
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

void QueryTree::setInited(bool b)
{
	inited = b;
}

void QueryTree::setSplitted(bool b)
{
	splitted = b;
}

void QueryTree::setValidated(bool b)
{
	validated = b;
}

void QueryTree::setEvaluated(bool b)
{
	evaluated = b;
}
 