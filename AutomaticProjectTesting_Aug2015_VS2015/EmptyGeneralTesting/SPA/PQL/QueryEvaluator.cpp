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
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

	if (type1 == "int" && type2 == "int")
	{
        //hasResult = isFollows(stoi(arg1), stoi(arg2));
	}
	else if (type1 == "int" && type2 == "_")
	{
        /*OK*/
        //hasResult = isBefore(stoi(arg1));
	}
	else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while")) 
	{
        /*OK*/
        pair<list<string>, list<string>> result;// = getAfter(stoi(arg1), arg2)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
	else if (type1 == "_" && type2 == "int")
	{ 
        /*OK*/
        //hasResult = isAfter(stoi(arg2));
	}
	else if (type1 == "_" && type2 == "_")
	{
        //hasResult = hasFollows();
	}
	else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<string>, list<string>> result;// = isFollowedBy(arg2)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
	{
        pair<list<string>, list<string>> result;// = isFollowedBy(arg1, stoi(arg2))
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
        pair<list<string>, list<string>> result;// = getAllBefore(arg1)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<string>, list<string>> result;// = getFollows(arg1, arg2)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
    else
    {
        cerr << "WTF JUST HAPPENED!" << endl;
    }
}

void QueryEvaluator::evaluateFollowsT(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
    {
        //hasResult = isFollowsT(stoi(arg1), stoi(arg2));
    }
    else if (type1 == "int" && type2 == "_")
    {
        //hasResult = isBeingFollowedT(stoi(arg1));
    }
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getAfterStar(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
        pair<list<string>, list<string>> result;// = getFollows(arg1, arg2)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
    }
    else if (type1 == "_" && type2 == "int")
    {
        //hasResult = isBeingFollowedByStar(arg2);
    }
    else if (type1 == "_" && type2 == "_")
    {
        //hasResult = hasFollowsT();
    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (isFollowedStarBy(arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
    {
        //if (isFollowedBy(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
    {
        //if (getAfter(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getFollows(arg1, arg2).empty()) {
        //
        //}
    }
    else
    {
        cerr << "WTF JUST HAPPENED!" << endl;
    }
}

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
	{
        //hasResult = isParent(arg1, arg2);
	}
	else if (type1 == "int" && type2 == "_")
	{
        //hasResult = isParent(arg1);
	}
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (getChildren(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if (type1 == "_" && type2 == "int")
	{
        //hasResult = isChildren(arg2);
	}
	else if (type1 == "_" && type2 == "_")
	{
        //hasResult = hasParent();
	}
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (isParentOf(arg2).empty()) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
	{
        //if (isParentOf(arg1, arg2)) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
	{
        //if (getChildren(arg1)) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (getParent(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
    else
    {
        cerr << "WTF JUST HAPPENED!" << endl;
    }
}

void QueryEvaluator::evaluateParentT(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
    {
        //hasResult = isParentStar(arg1, arg2);
    }
    else if (type1 == "int" && type2 == "_")
    {
        //hasResult = isParentStar(arg2);
    }
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getChildrenStar(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if (type1 == "_" && type2 == "int")
    {

    }
    else if (type1 == "_" && type2 == "_")
    {

    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {

    }
    else
    {
        cerr << "WTF JUST HAPPENED!" << endl;
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
		else 
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{
		list<string> result;// = getUsesFromVar(arg1, arg2);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> result;// = getStmtThatUsesAnything(arg1);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> result;// = getUses(arg1);
		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat = result;
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
		else
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{
		list<string> result;// = getModifiesFromVar(arg1, arg2);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> result;// = getStmtThatModifiesAnything(arg1);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat.first = result;
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> result;// = getModifies(arg1);
		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
		else
		{
			resultSuchThat = result;
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
