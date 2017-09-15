#include "QueryEvaluator.h"



QueryEvaluator::QueryEvaluator()
{
}


QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
}

void QueryEvaluator::evaluateFollows(array<string, 4> arr)
{

	if (arr[0] == "int" && arr[2] == "int")
	{

	}
	else if (arr[0] == "int" && arr[2] == "_")
	{

	}
	else if (arr[0] == "int" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while")) 
	{

	}
	else if (arr[0] == "_" && arr[2] == "int")
	{ 

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{

	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "int")
	{

	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "_")
	{

	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{

	}
}

void QueryEvaluator::evaluateFollowsT(array<string, 4> arr)
{
	if (arr[0] == "int" && arr[2] == "int")
	{

	}
	else if (arr[0] == "int" && arr[2] == "_")
	{

	}
	else if (arr[0] == "int" && arr[2] == "")
	{

	}
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
	{

	}
	else if (arr[0] == "" && arr[2] == "int")
	{

	}
	else if (arr[0] == "" && arr[2] == "_")
	{

	}
	else if (arr[0] == "" && arr[2] == "")
	{

	}
}

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
	if (arr[0] == "int" && arr[2] == "int")
	{

	}
	else if (arr[0] == "int" && arr[2] == "_")
	{

	}
	else if (arr[0] == "int" && arr[2] == "")
	{

	}
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
	{

	}
	else if (arr[0] == "" && arr[2] == "int")
	{

	}
	else if (arr[0] == "" && arr[2] == "_")
	{

	}
	else if (arr[0] == "" && arr[2] == "")
	{

	}
}

void QueryEvaluator::evaluateParentT(array<string, 4> arr)
{
	if (arr[0] == "int" && arr[2] == "int")
	{

	}
	else if (arr[0] == "int" && arr[2] == "_")
	{

	}
	else if (arr[0] == "int" && arr[2] == "")
	{

	}
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
	{

	}
	else if (arr[0] == "" && arr[2] == "int")
	{

	}
	else if (arr[0] == "" && arr[2] == "_")
	{

	}
	else if (arr[0] == "" && arr[2] == "")
	{

	}
}

void QueryEvaluator::evaluateUses(array<string, 4> arr)
{
	string type1 = arr[0];
	string type2 = arr[2];
	string arg1 = arr[1];
	string arr2 = arr[3];

	if (type1 == "int" && type2 == "ident")
	{
		int num = stoi(arg1);
		// hasResult = isUses(num, arg2);
	}
	else if (type1 == "int" && type2 == "_")
	{
		int num = stoi(arg1);
		// hasResult = isUsingAnything(num, arg2);
	}
	else if (type1 == "int" && type2 == "var")
	{
		int num = stoi(arg1);
		list<string> result;// = getUsesFromStmt(num);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{
		list<string> result;// = getUsesFromVar(arg1, arg2);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> result;// = getStmtThatUsesAnything(arg1);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> result;// = getUses(arg1);
		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
	}
	else
	{
		cerr << "WTF JUST HAPPENED!" << endl;
	}
}

void QueryEvaluator::evaluateModifies(array<string, 4> arr)
{
	string type1 = arr[0];
	string type2 = arr[2];
	string arg1 = arr[1];
	string arr2 = arr[3];

	if (type1 == "int" && type2 == "ident")
	{
		int num = stoi(arg1);
		// hasResult = isMod(num, arg2);
	}
	else if (type1 == "int" && type2 == "_")
	{
		int num = stoi(arg1);
		// hasResult = isModifyingAnything(num, arg2);
	}
	else if (type1 == "int" && type2 == "var")
	{
		int num = stoi(arg1);
		list<string> result;// = getModifiesFromStmt(num);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{
		list<string> result;// = getModifiesFromVar(arg1, arg2);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> result;// = getStmtThatModifiesAnything(arg1);
		if (result.empty())
		{
			hasResult = false;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> result;// = getModifies(arg1);
		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
	}
	else
	{
		cerr << "WTF JUST HAPPENED!" << endl;
	}
}

void QueryEvaluator::evaluatePattern(array<string, 6> arr)
{

}
