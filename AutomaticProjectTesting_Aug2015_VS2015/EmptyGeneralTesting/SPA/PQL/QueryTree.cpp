#include "QueryTree.h"

using namespace std;

QueryTree* QueryTree::instance = 0;

QueryTree::QueryTree()
{
}

QueryTree::~QueryTree()
{
}

QueryTree* QueryTree::getInstance()
{
	if (instance == 0) 
	{
		instance = new QueryTree();
	}

	return instance;
}

QueryTree* QueryTree::clear()
{
	instance = new QueryTree();
	return instance;
}

void QueryTree::storeUnvalidatedStmts(vector<string> splittedVec)
{
	unvalidatedStmts = splittedVec;
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
}

void QueryTree::insertFollows(array<string, 4> arr)
{
	followsClauses.push_back(arr);
}

void QueryTree::insertFollowsStar(array<string, 4> arr)
{
	followsStarClauses.push_back(arr);
}

void QueryTree::insertParent(array<string, 4> arr)
{
	parentClauses.push_back(arr);
}

void QueryTree::insertParentStar(array<string, 4> arr)
{
	parentStarClauses.push_back(arr);
}

void QueryTree::insertUses(array<string, 4> arr)
{
	usesClauses.push_back(arr);
}

void QueryTree::insertModifies(array<string, 4> arr)
{
	modifiesClauses.push_back(arr);
}

void QueryTree::insertPattern(array<string, 6> arr)
{
	patternClauses.push_back(arr);
}

void QueryTree::storeEvaluatorResult(list<string> list)
{
	evaluatorResult = list;
}

void QueryTree::insertSelect(array<string, 2> arr)
{
	selectStmt = arr;
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

array<string, 2> QueryTree::getSelect()
{
	return selectStmt;
}

vector<array<string, 4>> QueryTree::getFollows()
{
	return followsClauses;
}

vector<array<string, 4>> QueryTree::getFollowsT()
{
	return followsStarClauses;
}

vector<array<string, 4>> QueryTree::getParent()
{
	return parentClauses;
}

vector<array<string, 4>> QueryTree::getParentT()
{
	return parentStarClauses;
}

vector<array<string, 4>> QueryTree::getUses()
{
	return usesClauses;
}

vector<array<string, 4>> QueryTree::getModifies()
{
	return modifiesClauses;
}

vector<array<string, 6>> QueryTree::getPatterns()
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
 