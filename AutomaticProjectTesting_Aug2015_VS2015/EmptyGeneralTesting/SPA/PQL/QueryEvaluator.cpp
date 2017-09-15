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
        pair<list<string>, list<string>> result;// = getFollows(stoi(arg1), arg2)
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
        //hasResult = isBeingFollowedByStar(stoi(arg2));
    }
    else if (type1 == "_" && type2 == "_")
    {
        //hasResult = hasFollowsT();
    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        pair<list<string>, list<string>> result;// = isFollowedStarBy(arg2)
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
        pair<list<string>, list<string>> result;// = isFollowedBy(arg1, stoi(arg2)
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
        pair<list<string>, list<string>> result;// = getAfter(arg1, arg2)
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

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
	{
        //hasResult = isParent(stoi(arg1), stoi(arg2));
	}
	else if (type1 == "int" && type2 == "_")
	{
        //hasResult = isParent(stoi(arg1));
	}
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<string>, list<string>> result;// = getChildren(stoi(arg1), arg2)
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
        //hasResult = isChildren(stoi(arg2));
	}
	else if (type1 == "_" && type2 == "_")
	{
        //hasResult = hasParent();
	}
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<string>, list<string>> result;// = isParentOf(arg2)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
	{
        pair<list<string>, list<string>> result;// = isParentOf(arg1, stoi(arg2))
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
	{
        pair<list<string>, list<string>> result;// = getChildren(arg1)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
	}
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<string>, list<string>> result;// = (getParent(arg1, arg2)
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
        pair<list<string>, list<string>> result;// = getChildrenStar(stoi(arg1), arg2)
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
        //hasResult = isChildrenStar(stoi(arg1));
    }
    else if (type1 == "_" && type2 == "_")
    {
        //hasResult = hasParentStar();
    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        pair<list<string>, list<string>> result;// = isParentStarOf(arg2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
    {
        pair<list<string>, list<string>> result;// = isParentStarOf(arg1, stoi(arg2));
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
    {
        pair<list<string>, list<string>> result;// = getChildrenStar(arg1)
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }
    }
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        pair<list<string>, list<string>> result;// = getParentT(arg1, arg2)
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
    if (arr[2] == "var" && arr[4] == "_")
    {
        //resultPattern = getLeftVariables(assign,variable);
    }
    else if (arr[2] == "var" && arr[4] == "ident")
    {
        //resultPattern = getLeftVariablesThatMatchWith(assign,variable);
    }
    else if (arr[2] == "_" && arr[4] == "ident")
    {
        //resultPattern = getPartialMatchStmt(arr[5])
    }
    else if (arr[2] == "ident" && arr[4] == "ident")
    {
        //resultPattern = hasPartialBothMatches(arr[3],arr[5])
    }
    else if (arr[2] == "_" && arr[4] == "_")
    {
        //resultPattern = getAssignments();
    }
    else if (arr[2] == "ident" && arr[4] == "_")
    {
        //resultPattern = getAssignments(arr[3]);
    }

}

/*--------------- Evaluator helper methods ---------------*/

/*--------------- Find set intersection between two lists---------------*/
list<string> QueryEvaluator::getIntersection(list<string> list1, list<string> list2)
{
    list1.pop_front();
    list2.pop_front();
    list<string> result;
    set_intersection(list1.begin(), list1.end(), list2.begin(), list2.end(), back_inserter(result));
    return result;
}
