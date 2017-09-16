#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator()
{
	qtInstance = QueryTree::getInstance();
}


QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
    
	if (hasResult)
	{
		array<string, 2> arr = qtInstance->getSelect();
		evaluateSelect(arr);
	}

	if (hasResult) 
	{
		vector<array<string, 4>> vec = qtInstance->getFollows();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateFollows(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 4>> vec = qtInstance->getFollowsT();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateFollowsT(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 4>> vec = qtInstance->getParent();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateParent(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 4>> vec = qtInstance->getParentT();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateParentT(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 4>> vec = qtInstance->getUses();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateUses(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 4>> vec = qtInstance->getModifies();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluateModifies(vec.at(i));
		}
	}

	if (hasResult)
	{
		vector<array<string, 6>> vec = qtInstance->getPatterns();
		for (int i = 0; i < vec.size(); i++)
		{
			evaluatePattern(vec.at(i));
		}
	}

    finalResult = getCommonSynonymResult(resultSelect, resultSuchThat, resultPattern);
}

/*--------------- Unit Testing ---------------*/
void QueryEvaluator::setPkb(PKBMain& pkb)
{
    PKB = pkb;
}

bool QueryEvaluator::getHasResult()
{
    return hasResult;
}

pair<list<string>, list<string>> QueryEvaluator::getResultSuchThat()
{
    return resultSuchThat;
}

list<string> QueryEvaluator::getIntersectionTest(list<string> list1, list<string> list2)
{
    return getIntersection(list1, list2);
}

void QueryEvaluator::evaluateSelectTest(array<string, 2> arr)
{
    evaluateSelect(arr);
}

void QueryEvaluator::evaluateFollowsTest(array<string, 4> arr)
{
    evaluateFollows(arr);
}

void QueryEvaluator::evaluateFollowsTTest(array<string, 4> arr)
{
    evaluateFollowsT(arr);
}

void QueryEvaluator::evaluateParentTest(array<string, 4> arr)
{
    evaluateParent(arr);
}

void QueryEvaluator::evaluateParentTTest(array<string, 4> arr)
{
    evaluateParentT(arr);
}

void QueryEvaluator::evaluateUsesTest(array<string, 4> arr)
{
    evaluateUses(arr);
}

void QueryEvaluator::evaluateModifiesTest(array<string, 4> arr)
{
    evaluateModifies(arr);
}

void QueryEvaluator::evaluatePatternTest(array<string, 6> arr)
{
    evaluatePattern(arr);
}

/*--------------- Evaluator private methods clauses ---------------*/

void QueryEvaluator::evaluateSelect(array<string, 2> arr)
{

	string type = arr[0];
	string synonym = arr[1];

	if (type == "stmt")
	{
		// resultSelect = getAllStmts();
	}
	else if (type == "assign")
	{
		// resultSelect = getAllAssignments();
	}
	else if (type == "while")
	{
		// resultSelect = getAllWhiles();
	}
	else if (type == "variable")
	{
		// resultSelect = getAllVars();
	}
	else
	{
		cerr << "WTF JUST HAPPENED!" << endl;
	}
}

void QueryEvaluator::evaluateFollows(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

	if (type1 == "int" && type2 == "int")
	{
        hasResult = PKB.isFollows(stoi(arg1), stoi(arg2));
	}
	else if (type1 == "int" && type2 == "_")
	{
        hasResult = PKB.isBefore(stoi(arg1));
	}
	else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while")) 
	{
        list<int> result = PKB.getAfter(stoi(arg1), type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
	else if (type1 == "_" && type2 == "int")
	{ 
        hasResult = PKB.isAfter(stoi(arg2));
	}
	else if (type1 == "_" && type2 == "_")
	{
        hasResult = PKB.hasFollows();
	}
	else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        list<int> result = PKB.getAllAfter(arg2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
	{
        /*list<string> result = PKB.getBefore(arg1, stoi(arg2));
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            resultSuchThat = result;
        }*/
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
        list<int> result = PKB.getAllBefore(type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<int>, list<int>> result = PKB.getAllFollows(arg1, arg2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result.first);
            list<string> list2 = getListStringFromListInt(result.second);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
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
	string arg2 = arr[3];

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
		list<string> pkbResult;// = getUsesFromStmt(num);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg2);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{

		list<string> pkbResult;// = getUsesFromVar(arg1, arg2);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg1);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> pkbResult;// = getStmtThatUsesAnything(arg1);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg1);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> pkbResult;// = getUsesPairs(arg1);

		if (pkbResult.first.empty() && pkbResult.second.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst1 = resultSuchThat.first;
			lst1.push_back(arg1);
			lst1.insert(lst1.end(), pkbResult.first.begin(), pkbResult.first.end());

			list<string> lst2 = resultSuchThat.second;
			lst2.push_back(arg2);
			lst2.insert(lst2.end(), pkbResult.first.begin(), pkbResult.first.end());
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
	string arg2 = arr[3];

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
		list<string> pkbResult;// = getModifiesFromStmt(num);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg2);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{

		list<string> pkbResult;// = getModifiesFromVar(arg1, arg2);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg1);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> pkbResult;// = getStmtThatModifiesAnything(arg1);

		if (pkbResult.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst = resultSuchThat.first;
			lst.push_back(arg1);
			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
		}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<string>, list<string>> pkbResult;// = getModifiesPairs(arg1);

		if (pkbResult.first.empty() && pkbResult.second.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> lst1 = resultSuchThat.first;
			lst1.push_back(arg1);
			lst1.insert(lst1.end(), pkbResult.first.begin(), pkbResult.first.end());

			list<string> lst2 = resultSuchThat.second;
			lst2.push_back(arg2);
			lst2.insert(lst2.end(), pkbResult.first.begin(), pkbResult.first.end());
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
    list<string> tempList1 = list1;
    list<string> tempList2 = list2;

    tempList1.pop_front();
    tempList2.pop_front();
    tempList1.sort();
    tempList2.sort();

    list<string> result;
    set_intersection(tempList1.begin(), tempList1.end(), tempList2.begin(), tempList2.end(), back_inserter(result));
    return result;
}

list<string> QueryEvaluator::getCommonSynonymResult(list<string> select, pair<list<string>, list<string>> suchThat, pair<list<string>, list<string>> pattern)
{
    list<string> tempResult = {};
    list<string> tempResultSuchThat;
    list<string> tempResultPattern;

    if (select.empty())
        return tempResult;

    tempResultSuchThat = select;
    tempResultPattern = select;

    tempResultSuchThat.pop_front();
    tempResultPattern.pop_front();
    tempResultSuchThat.sort();
    tempResultPattern.sort();

    if (!suchThat.first.empty() || !suchThat.second.empty())
    {
        if (!suchThat.first.empty()) 
        {
            if (select.front() == suchThat.first.front())
                tempResultSuchThat = getIntersection(select, suchThat.first);
        }

        if (!suchThat.second.empty())
        {
            if (select.front() == suchThat.second.front()) 
            {
                tempResultSuchThat = getIntersection(select, suchThat.second);
            }
        }
    }

    if (!pattern.first.empty() || !pattern.second.empty())
    {
        if (!pattern.first.empty())
        {
            if (select.front() == pattern.first.front()) 
            {
                tempResultPattern = getIntersection(select, pattern.first);
            }
        }

        if (!pattern.second.empty())
        {
            if (select.front() == pattern.second.front())
                tempResultPattern = getIntersection(select, pattern.second);
        }
    }

    set_intersection(tempResultSuchThat.begin(), tempResultSuchThat.end(), tempResultPattern.begin(), tempResultPattern.end(), back_inserter(tempResult));
    return tempResult;
}

list<string> QueryEvaluator::getListStringFromListInt(list<int> listOfInt)
{
    list<string> listOfString;
    for (std::list<int>::iterator it = listOfInt.begin(); it != listOfInt.end(); ++it) {
        string stringFromInt = to_string(*it);
        listOfString.push_back(stringFromInt);
    }
    return listOfString;
}