#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator()
{
	qtInstance = QueryTree::getInstance();
	pkbInstance = PKBMain::getInstance();
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
			evaluateFollowsStar(vec.at(i));
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
			evaluateParentStar(vec.at(i));
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
    qtInstance->storeEvaluatorResult(finalResult);
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

void QueryEvaluator::evaluateFollowsStarTest(array<string, 4> arr)
{
    evaluateFollowsStar(arr);
}

void QueryEvaluator::evaluateParentTest(array<string, 4> arr)
{
    evaluateParent(arr);
}

void QueryEvaluator::evaluateParentStarTest(array<string, 4> arr)
{
    evaluateParentStar(arr);
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
		resultSelect = getListStringFromListInt(pkbInstance->getAllStatements());
        resultSelect.push_front(synonym);
	}
	else if (type == "assign")
	{
		resultSelect = getListStringFromListInt(pkbInstance->getAllAssignments());
        resultSelect.push_front(synonym);
	}
	else if (type == "while")
	{
		resultSelect = getListStringFromListInt(pkbInstance->getAllWhiles());
        resultSelect.push_front(synonym);
	}
	else if (type == "var")
	{
		resultSelect = pkbInstance->getAllVariables();
        resultSelect.push_front(synonym);
	}
	else
	{
		cerr << "Wrong evaluation!" << endl;
	}
}

void QueryEvaluator::evaluateFollows(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

    //Case 1: Follows(int, int)
	if (type1 == "int" && type2 == "int")
	{
        hasResult = pkbInstance->isFollows(stoi(arg1), stoi(arg2));
	}
    //Case 2: Follows(int, _)
	else if (type1 == "int" && type2 == "_")
	{
        hasResult = pkbInstance->isBefore(stoi(arg1));
	}
    //Case 3: Follows(int, synonym)
	else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while")) 
	{
        list<int> result = pkbInstance->getAfter(stoi(arg1), type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);     
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 4: Follows(_, int)
	else if (type1 == "_" && type2 == "int")
	{ 
        hasResult = pkbInstance->isAfter(stoi(arg2));
	}
    //Case 5: Follows(_, _)
	else if (type1 == "_" && type2 == "_")
	{
        hasResult = pkbInstance->hasFollows();
	}
    //Case 6: Follows(_, synonym)
	else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        list<int> result = pkbInstance->getAllAfter(arg2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 7: Follows(synonym, int)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
	{
        list<int> result = pkbInstance->getBefore(stoi(arg2), type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 8: Follows(synonym, _)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
        list<int> result = pkbInstance->getAllBefore(type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 9: Follows(synonym, synonym)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<int>, list<int>> result = pkbInstance->getAllFollows(type1, type2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result.first);
            list<string> list2 = getListStringFromListInt(result.second);
            list1.push_front(arg1);
            list2.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    else
    {
        cerr << "Wrong evaluation!!" << endl;
    }
}

void QueryEvaluator::evaluateFollowsStar(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

    //Case 1: FollowsStar(int, int)
    if (type1 == "int" && type2 == "int")
    {
        hasResult = pkbInstance->isFollowsStar(stoi(arg1), stoi(arg2));
    }
    //Case 2: FollowsStar(int, _)
    else if (type1 == "int" && type2 == "_")
    {
        hasResult = pkbInstance->isBefore(stoi(arg1));
    }
    //Case 3: FollowsStar(int, synonym)
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        list<int> result = pkbInstance->getAfterStar(stoi(arg1), type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;

        }
    }
    //Case 4: FollowsStar(_, int)
    else if (type1 == "_" && type2 == "int")
    {
        hasResult = pkbInstance->isAfter(stoi(arg2));
    }
    //Case 5: FollowsStar(_, _)
    else if (type1 == "_" && type2 == "_")
    {
        hasResult = pkbInstance->hasFollows();
    }
    //Case 6: FollowsStar(_, synonym)
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        list<int> result = pkbInstance->getAllAfterStar(type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 7: FollowsStar(synonym, int)
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
    {
        list<int> result = pkbInstance->getBefore(stoi(arg2), type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 8: FollowsStar(synonym, _)
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
    {
        list<int> result = pkbInstance->getAllBeforeStar(type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 9: FollowsStar(synonym, synonym)
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        pair<list<int>, list<int>> result = pkbInstance->getAllFollowsStar(type1, type2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result.first);
            list<string> list2 = getListStringFromListInt(result.second);
            list1.push_front(arg1);
            list2.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    else
    {
        cerr << "Wrong evaluation!!" << endl;
    }
}

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

    //Case 1: Parent(int, int)
    if (type1 == "int" && type2 == "int")
	{
        hasResult = pkbInstance->isParentChild(stoi(arg1), stoi(arg2));
	}
    //Case 2: Parent(int, _)
	else if (type1 == "int" && type2 == "_")
	{
        hasResult = pkbInstance->isParent(stoi(arg1));
	}
    //Case 3: Parent(int, synonym)
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        list<int> result = pkbInstance->getChildren(stoi(arg1), type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 4: Parent(_, int)
	else if (type1 == "_" && type2 == "int")
	{
        hasResult = pkbInstance->isChild(stoi(arg2));
	}
    //Case 5: Parent(_, _)
	else if (type1 == "_" && type2 == "_")
	{
        hasResult = pkbInstance->hasParentRel();
	}
    //Case 6: Parent(_, synonym)
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        list<int> result = pkbInstance->getAllChildren(type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 7: Parent(synonym, int)
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
	{
        list<int> result = pkbInstance->getParent(stoi(arg2), type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 8: Parent(synonym, _)
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
	{
        list<int> result = pkbInstance->getAllParents(type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    //Case 9: Parent(synonym, synonym)
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        pair<list<int>, list<int>> result = PKB.getAllParentsRel(type1, type2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result.first);
            list<string> list2 = getListStringFromListInt(result.second);
            list1.push_front(arg1);
            list2.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
	}
    else
    {
        cerr << "Wrong evaluation!!" << endl;
    }
}

void QueryEvaluator::evaluateParentStar(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

    //Case 1: ParentStar(int, int)
    if (type1 == "int" && type2 == "int")
    {
        hasResult = pkbInstance->isParentStarChild(stoi(arg1), stoi(arg2));
    }
    //Case 2: ParentStar(int, _)
    else if (type1 == "int" && type2 == "_")
    {
        hasResult = pkbInstance->isParent(stoi(arg1));
    }
    //Case 3: ParentStar(int, synonym)
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        list<int> result = pkbInstance->getChildrenStar(stoi(arg1), type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 4: ParentStar(_, int)
    else if (type1 == "_" && type2 == "int")
    {
        hasResult = pkbInstance->isChild(stoi(arg2));
    }
    //Case 5: ParentStar(_, _)
    else if (type1 == "_" && type2 == "_")
    {
        hasResult = pkbInstance->hasParentRel();
    }
    //Case 6: ParentStar(_, synonym)
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        list<int> result = pkbInstance->getAllChildren(type2);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 7: ParentStar(synonym, int)
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
    {
       /* list<int> result = pkbInstance->getParent(type1, stoi(arg2));
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
        }*/
    }
    //Case 8: ParentStar(synonym, _)
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
    {
        list<int> result = PKB.getAllParents(type1);
        if (result.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result);
            list<string> list2;
            list1.push_front(arg1);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    //Case 9: ParentStar(synonym, synonym)
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        pair<list<int>, list<int>> result = pkbInstance->getAllParentStarRel(type1, type2);
        if (result.first.empty() && result.second.empty())
        {
            hasResult = false;
        }
        else
        {
            list<string> list1 = getListStringFromListInt(result.first);
            list<string> list2 = getListStringFromListInt(result.second);
            list1.push_front(arg1);
            list2.push_front(arg2);
            resultSuchThat = make_pair(list1, list2);
            hasResult = true;
        }
    }
    else
    {
        cerr << "Wrong evaluation!!" << endl;
    }
}

void QueryEvaluator::evaluateUses(array<string, 4> arr)
{
	string type1 = arr[0];
	string type2 = arr[2];
	string arg1 = arr[1];
	string arg2 = arr[3];

    //Case 1: Uses(int, ident)
	if (type1 == "int" && type2 == "ident")
	{
		int num = stoi(arg1);
		hasResult = pkbInstance->isUses(num, arg2);
	}
    //Case 2: Uses(int, _)
	else if (type1 == "int" && type2 == "_")
	{
		int num = stoi(arg1);
		hasResult = pkbInstance->isUsingAnything(num);
	}
    //Case 3: Uses(int, var)
	else if (type1 == "int" && type2 == "var")
	{
		int num = stoi(arg1);
		list<string> pkbResult = pkbInstance->getUsesFromStmt(num);

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
    //Case 4: Uses(synonym, ident)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{

		list<string> pkbResult = getListStringFromListInt(pkbInstance->getUsesFromVar(arg1, arg2));
		

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
    //Case 5: Uses(synonyym, _)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> pkbResult = getListStringFromListInt(pkbInstance->getStmtThatUsesAnything(arg1));

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
    //Case 6: Uses(synonym, var)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<int>, list<string>> pkbResult = pkbInstance->getUsesPairs(arg1);

		if (pkbResult.first.empty() && pkbResult.second.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
			list<string> lst1 = resultSuchThat.first;			
			lst1.push_back(arg1);
			lst1.insert(lst1.end(), pkbResultFirst.begin(), pkbResultFirst.end());

			list<string> lst2 = resultSuchThat.second;
			lst2.push_back(arg2);
			lst2.insert(lst2.end(), pkbResult.second.begin(), pkbResult.second.end());
		}
	}
	else
	{
		cerr << "Wrong evaluation!!" << endl;
	}
}

void QueryEvaluator::evaluateModifies(array<string, 4> arr)
{
	string type1 = arr[0];
	string type2 = arr[2];
	string arg1 = arr[1];
	string arg2 = arr[3];

	//Case 1: Modifies(int, ident)
	if (type1 == "int" && type2 == "ident")
	{
		int num = stoi(arg1);
		hasResult = pkbInstance->isMod(num, arg2);
	}
	//Case 2: Modifies(int, _)
	else if (type1 == "int" && type2 == "_")
	{
		int num = stoi(arg1);
		hasResult = pkbInstance->isModifyingAnything(num);
	}
	//Case 3: Modifies(int, var)
	else if (type1 == "int" && type2 == "var")
	{
		int num = stoi(arg1);
		list<string> pkbResult = pkbInstance->getModifiesFromStmt(num);

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
	//Case 4: Modifies(synonym, ident)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "ident")
	{

		list<string> pkbResult = getListStringFromListInt(pkbInstance->getModifiesFromVar(arg1, arg2));


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
	//Case 5: Modifies(synonyym, _)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
		list<string> pkbResult = getListStringFromListInt(pkbInstance->getStmtThatModifiesAnything(arg1));

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
	//Case 6: Modifies(synonym, var)
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "var")
	{
		pair<list<int>, list<string>> pkbResult = pkbInstance->getModifiesPairs(arg1);

		if (pkbResult.first.empty() && pkbResult.second.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
			list<string> lst1 = resultSuchThat.first;
			lst1.push_back(arg1);
			lst1.insert(lst1.end(), pkbResultFirst.begin(), pkbResultFirst.end());

			list<string> lst2 = resultSuchThat.second;
			lst2.push_back(arg2);
			lst2.insert(lst2.end(), pkbResult.second.begin(), pkbResult.second.end());
		}
	}
	else
	{
		cerr << "Wrong evaluation!!" << endl;
	}
}

void QueryEvaluator::evaluatePattern(array<string, 6> arr)
{
    string type1 = arr[2];
    string type2 = arr[4];
    string arg1 = arr[3];
    string arg2 = arr[5];
    if (type1 == "var" && type2 == "_")
    {
        // list<int> assign = PKB.getLeftVariables.first;
        // list<string> var = PKB.getLeftVariables.second;
        //resultPattern = pair<intToString(assign),var>;
    }
    else if (type1 == "var" && type2 == "ident")
    {
        //resultPattern = getLeftVariablesThatMatchWith(assign,variable);
    }
    else if (type1 == "_" && type2 == "ident")
    {
        //resultPattern = getPartialMatchStmt(arr[5])
    }
    else if (type1 == "ident" && type2 == "ident")
    {
        //resultPattern = hasPartialBothMatches(arr[3],arr[5])
    }
    else if (type1 == "_" && type2 == "_")
    {
        //resultPattern = getAssignments();
    }
    else if (type1 == "ident" && type2 == "_")
    {
        //resultPattern = getAssignments(arr[3]);
    }
    else
    {
        cerr << "Wrong evaluation!!" << endl;
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
