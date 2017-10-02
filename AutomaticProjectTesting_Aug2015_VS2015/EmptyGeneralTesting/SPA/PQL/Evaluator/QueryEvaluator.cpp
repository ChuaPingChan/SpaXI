#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(QueryTree* qtPtr)
{
    this->_qt = qtPtr;
}

QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
    bool hasResult = true;
    ClauseResult clauseResult;
    ResultFactory factory = ResultFactory(clauseResult);

    for (SuchThatClause stClause : _qt->getSuchThatClauses())
    {

    }
}



//QueryEvaluator::QueryEvaluator()
//{
//	qtInstance = QueryTree::getInstance();
//	pkbInstance = PKBMain::getInstance();
//}
//
//
//QueryEvaluator::~QueryEvaluator()
//{
//}
//
//void QueryEvaluator::evaluate()
//{
//    
//	if (hasResult)
//	{
//		array<string, 2> arr = qtInstance->getSelect();
//		evaluateSelect(arr);
//	}
//
//	if (hasResult) 
//	{
//		vector<array<string, 4>> vec = qtInstance->getFollows();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateFollows(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 4>> vec = qtInstance->getFollowsT();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateFollowsStar(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 4>> vec = qtInstance->getParent();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateParent(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 4>> vec = qtInstance->getParentT();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateParentStar(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 4>> vec = qtInstance->getUses();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateUses(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 4>> vec = qtInstance->getModifies();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluateModifies(vec.at(i));
//		}
//	}
//
//	if (hasResult)
//	{
//		vector<array<string, 6>> vec = qtInstance->getPatterns();
//		for (int i = 0; i < vec.size(); i++)
//		{
//			evaluatePattern(vec.at(i));
//		}
//	}
//
//	if (hasResult) 
//	{
//		finalResult = getCommonSynonymResult(resultSelect, resultSuchThat, resultPattern);
//
//		qtInstance->storeEvaluatorResult(finalResult);
//	}
//}
//
///*--------------- Unit Testing ---------------*/
//void QueryEvaluator::setPkb(PKBMain& pkb)
//{
//    PKB = pkb;
//}
//
//bool QueryEvaluator::getHasResult()
//{
//    return hasResult;
//}
//
//pair<list<string>, list<string>> QueryEvaluator::getResultSuchThat()
//{
//    return resultSuchThat;
//}
//
//list<string> QueryEvaluator::getIntersectionTest(list<string> list1, list<string> list2)
//{
//    return getIntersection(list1, list2);
//}
//
//void QueryEvaluator::evaluateSelectTest(array<string, 2> arr)
//{
//    evaluateSelect(arr);
//}
//
//void QueryEvaluator::evaluateFollowsTest(array<string, 4> arr)
//{
//    evaluateFollows(arr);
//}
//
//void QueryEvaluator::evaluateFollowsStarTest(array<string, 4> arr)
//{
//    evaluateFollowsStar(arr);
//}
//
//void QueryEvaluator::evaluateParentTest(array<string, 4> arr)
//{
//    evaluateParent(arr);
//}
//
//void QueryEvaluator::evaluateParentStarTest(array<string, 4> arr)
//{
//    evaluateParentStar(arr);
//}
//
//void QueryEvaluator::evaluateUsesTest(array<string, 4> arr)
//{
//    evaluateUses(arr);
//}
//
//void QueryEvaluator::evaluateModifiesTest(array<string, 4> arr)
//{
//    evaluateModifies(arr);
//}
//
//void QueryEvaluator::evaluatePatternTest(array<string, 6> arr)
//{
//    evaluatePattern(arr);
//}
//
///*--------------- Evaluator private methods clauses ---------------*/
//
//void QueryEvaluator::evaluateSelect(array<string, 2> arr)
//{
//
//	string type = arr[0];
//	string synonym = arr[1];
//
//	if (type == STMT)
//	{
//		resultSelect = getListStringFromListInt(pkbInstance->getAllStatements());
//        resultSelect.push_front(synonym);
//	}
//	else if (type == ASSIGN)
//	{
//		resultSelect = getListStringFromListInt(pkbInstance->getAllAssignments());
//        resultSelect.push_front(synonym);
//	}
//	else if (type == WHILE)
//	{
//		resultSelect = getListStringFromListInt(pkbInstance->getAllWhiles());
//        resultSelect.push_front(synonym);
//	}
//	else if (type == "var")
//	{
//		resultSelect = pkbInstance->getAllVariables();
//        resultSelect.push_front(synonym);
//	}
//    else if (type == "const")
//    {
//        resultSelect = getListStringFromListInt(pkbInstance->getAllConstants());
//        resultSelect.push_front(synonym);
//    }
//	else
//	{
//		cerr << "Unrecognised type: <" << type << ", " << synonym << ">" << endl;
//	}
//}
//
//void QueryEvaluator::evaluateFollows(array<string, 4> arr)
//{
//    string argOneType = arr[0];
//    string argTwoType = arr[2];
//    string argOne = arr[1];
//    string argTwo = arr[3];
//
//    //Case 1: Follows(int, int)
//	if (argOneType == INTEGER && argTwoType == INTEGER)
//	{
//        hasResult = pkbInstance->isFollows(stoi(argOne), stoi(argTwo));
//	}
//    //Case 2: Follows(int, _)
//	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//	{
//        hasResult = pkbInstance->isBefore(stoi(argOne));
//	}
//    //Case 3: Follows(int, synonym)
//	else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE)) 
//	{
        //list<int> result = pkbInstance->getAfter(stoi(argOne), argTwoType);
        //if (result.empty())
        //{
        //    hasResult = false;
        //}
        //else
        //{
        //    ClauseResult->
        //    hasResult = true;
        //}
//	}
//    //Case 4: Follows(_, int)
//	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
//	{ 
//        hasResult = pkbInstance->isAfter(stoi(argTwo));
//	}
//    //Case 5: Follows(_, _)
//	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
//	{
//        hasResult = pkbInstance->hasFollows();
//	}
//    //Case 6: Follows(_, synonym)
//	else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//	{
//        list<int> result = pkbInstance->getAllAfter(argTwo);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 7: Follows(synonym, int)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == INTEGER)
//	{
//        list<int> result = pkbInstance->getBefore(stoi(argTwo), argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 8: Follows(synonym, _)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
//	{
//        list<int> result = pkbInstance->getAllBefore(argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 9: Follows(synonym, synonym)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//	{
//        pair<list<int>, list<int>> result = pkbInstance->getAllFollows(argOneType, argTwoType);
//        if (result.first.empty() && result.second.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result.first);
//            list<string> list2 = getListStringFromListInt(result.second);
//            list1.push_front(argOne);
//            list2.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    else
//    {
//		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//    }
//}
//
//void QueryEvaluator::evaluateFollowsStar(array<string, 4> arr)
//{
//    string argOneType = arr[0];
//    string argTwoType = arr[2];
//    string argOne = arr[1];
//    string argTwo = arr[3];
//
//    //Case 1: FollowsStar(int, int)
//    if (argOneType == INTEGER && argTwoType == INTEGER)
//    {
//        hasResult = pkbInstance->isFollowsStar(stoi(argOne), stoi(argTwo));
//    }
//    //Case 2: FollowsStar(int, _)
//    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//    {
//        hasResult = pkbInstance->isBefore(stoi(argOne));
//    }
//    //Case 3: FollowsStar(int, synonym)
//    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        list<int> result = pkbInstance->getAfterStar(stoi(argOne), argTwoType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//
//        }
//    }
//    //Case 4: FollowsStar(_, int)
//    else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
//    {
//        hasResult = pkbInstance->isAfter(stoi(argTwo));
//    }
//    //Case 5: FollowsStar(_, _)
//    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
//    {
//        hasResult = pkbInstance->hasFollows();
//    }
//    //Case 6: FollowsStar(_, synonym)
//    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        list<int> result = pkbInstance->getAllAfterStar(argTwoType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 7: FollowsStar(synonym, int)
//    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == INTEGER)
//    {
//        list<int> result = pkbInstance->getBeforeStar(stoi(argTwo), argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 8: FollowsStar(synonym, _)
//    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
//    {
//        list<int> result = pkbInstance->getAllBeforeStar(argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 9: FollowsStar(synonym, synonym)
//    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        pair<list<int>, list<int>> result = pkbInstance->getAllFollowsStar(argOneType, argTwoType);
//        if (result.first.empty() && result.second.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result.first);
//            list<string> list2 = getListStringFromListInt(result.second);
//            list1.push_front(argOne);
//            list2.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    else
//    {
//        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//    }
//}
//
//void QueryEvaluator::evaluateParent(array<string, 4> arr)
//{
//    string argOneType = arr[0];
//    string argTwoType = arr[2];
//    string argOne = arr[1];
//    string argTwo = arr[3];
//
//    //Case 1: Parent(int, int)
//    if (argOneType == INTEGER && argTwoType == INTEGER)
//	{
//        hasResult = pkbInstance->isParentChild(stoi(argOne), stoi(argTwo));
//	}
//    //Case 2: Parent(int, _)
//	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//	{
//        hasResult = pkbInstance->isParent(stoi(argOne));
//	}
//    //Case 3: Parent(int, synonym)
//    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//	{
//        list<int> result = pkbInstance->getChildren(stoi(argOne), argTwoType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 4: Parent(_, int)
//	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
//	{
//        hasResult = pkbInstance->isChild(stoi(argTwo));
//	}
//    //Case 5: Parent(_, _)
//	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
//	{
//        hasResult = pkbInstance->hasParentRel();
//	}
//    //Case 6: Parent(_, synonym)
//    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//	{
//        list<int> result = pkbInstance->getAllChildren(argTwoType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 7: Parent(synonym, int)
//    else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == INTEGER)
//	{
//        list<int> result = pkbInstance->getParent(stoi(argTwo), argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 8: Parent(synonym, _)
//    else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == UNDERSCORE)
//	{
//        list<int> result = pkbInstance->getAllParents(argOneType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    //Case 9: Parent(synonym, synonym)
//    else if ((argOneType == STMT || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        pair<list<int>, list<int>> result = pkbInstance->getAllParentsRel(argOneType, argTwoType);
//        if (result.first.empty() && result.second.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result.first);
//            list<string> list2 = getListStringFromListInt(result.second);
//            list1.push_front(argOne);
//            list2.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//	}
//    else
//    {
//        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//    }
//}
//
//void QueryEvaluator::evaluateParentStar(array<string, 4> arr)
//{
//    string argOneType = arr[0];
//    string argTwoType = arr[2];
//    string argOne = arr[1];
//    string argTwo = arr[3];
//
//    //Case 1: ParentStar(int, int)
//    if (argOneType == INTEGER && argTwoType == INTEGER)
//    {
//        hasResult = pkbInstance->isParentStarChild(stoi(argOne), stoi(argTwo));
//    }
//    //Case 2: ParentStar(int, _)
//    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//    {
//        hasResult = pkbInstance->isParent(stoi(argOne));
//    }
//    //Case 3: ParentStar(int, synonym)
//    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        list<int> result = pkbInstance->getChildrenStar(stoi(argOne), argTwoType);
//
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 4: ParentStar(_, int)
//    else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
//    {
//        hasResult = pkbInstance->isChild(stoi(argTwo));
//    }
//    //Case 5: ParentStar(_, _)
//    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
//    {
//        hasResult = pkbInstance->hasParentRel();
//    }
//    //Case 6: ParentStar(_, synonym)
//    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        list<int> result = pkbInstance->getAllChildren(argTwoType);
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 7: ParentStar(int, synonym)
//    else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == INTEGER)
//    {
//        list<int> result = pkbInstance->getParentStar(stoi(argTwo), argOneType);
//
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//
//            hasResult = true;
//        }
//    }
//    //Case 8: ParentStar(synonym, _)
//    else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == UNDERSCORE)
//    {
//
//        list<int> result = pkbInstance->getAllParents(argOneType);
//
//
//        if (result.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result);
//            list<string> list2;
//            list1.push_front(argOne);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    //Case 9: ParentStar(synonym, synonym)
//    else if ((argOneType == STMT || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
//    {
//        pair<list<int>, list<int>> result = pkbInstance->getAllParentStarRel(argOneType, argTwoType);
//        if (result.first.empty() && result.second.empty())
//        {
//            hasResult = false;
//        }
//        else
//        {
//            list<string> list1 = getListStringFromListInt(result.first);
//            list<string> list2 = getListStringFromListInt(result.second);
//            list1.push_front(argOne);
//            list2.push_front(argTwo);
//            resultSuchThat = make_pair(list1, list2);
//            hasResult = true;
//        }
//    }
//    else
//    {
//        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//    }
//}
//
//void QueryEvaluator::evaluateUses(array<string, 4> arr)
//{
//	string argOneType = arr[0];
//	string argTwoType = arr[2];
//	string argOne = arr[1];
//	string argTwo = arr[3];
//
//    //Case 1: Uses(int, ident)
//	if (argOneType == INTEGER && argTwoType == "ident")
//	{
//		int num = stoi(argOne);
//		string ident = regex_replace(argTwo, regex("\""), "");
//		hasResult = pkbInstance->isUses(num, ident);
//	}
//    //Case 2: Uses(int, _)
//	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//	{
//		int num = stoi(argOne);
//		hasResult = pkbInstance->isUsingAnything(num);
//	}
//    //Case 3: Uses(int, var)
//	else if (argOneType == INTEGER && argTwoType == "var")
//	{
//		int num = stoi(argOne);
//		list<string> pkbResult = pkbInstance->getUsesFromStmt(num);
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argTwo);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//    //Case 4: Uses(synonym, ident)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == "ident")
//	{
//		string ident = regex_replace(argTwo, regex("\""), "");
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getUsesFromVar(ident, argOneType));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//    //Case 5: Uses(synonyym, _)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
//	{
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getStmtThatUsesAnything(argOneType));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//    //Case 6: Uses(synonym, var)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == "var")
//	{
//		pair<list<int>, list<string>> pkbResult = pkbInstance->getUsesPairs(argOneType);
//
//		if (pkbResult.first.empty() && pkbResult.second.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResultFirst.begin(), pkbResultFirst.end());
//
//			list<string> lst2 = resultSuchThat.second;
//			lst2.push_back(argTwo);
//			lst2.insert(lst2.end(), pkbResult.second.begin(), pkbResult.second.end());
//
//			resultSuchThat = make_pair(lst, lst2);
//			hasResult = true;
//		}
//	}
//	else
//	{
//		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//	}
//}
//
//void QueryEvaluator::evaluateModifies(array<string, 4> arr)
//{
//	string argOneType = arr[0];
//	string argTwoType = arr[2];
//	string argOne = arr[1];
//	string argTwo = arr[3];
//
//	//Case 1: Modifies(int, ident)
//	if (argOneType == INTEGER && argTwoType == "ident")
//	{
//		int num = stoi(argOne);
//		string ident = regex_replace(argTwo, regex("\""), "");
//		hasResult = pkbInstance->isMod(num, ident);
//	}
//	//Case 2: Modifies(int, _)
//	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
//	{
//		int num = stoi(argOne);
//		hasResult = pkbInstance->isModifyingAnything(num);
//	}
//	//Case 3: Modifies(int, var)
//	else if (argOneType == INTEGER && argTwoType == "var")
//	{
//		int num = stoi(argOne);
//		list<string> pkbResult = pkbInstance->getModifiesFromStmt(num);
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argTwo);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//	//Case 4: Modifies(synonym, ident)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == "ident")
//	{
//		string ident = regex_replace(argTwo, regex("\""), "");
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getModifiesFromVar(ident, argOneType));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//	//Case 5: Modifies(synonym, _)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
//	{
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getStmtThatModifiesAnything(argOneType));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResult.begin(), pkbResult.end());
//			resultSuchThat = make_pair(lst, list<string>());
//			hasResult = true;
//		}
//	}
//	//Case 6: Modifies(synonym, var)
//	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == "var")
//	{
//		pair<list<int>, list<string>> pkbResult = pkbInstance->getModifiesPairs(argOneType);
//
//		if (pkbResult.first.empty() && pkbResult.second.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
//			list<string> lst = resultSuchThat.first;
//			lst.push_back(argOne);
//			lst.insert(lst.end(), pkbResultFirst.begin(), pkbResultFirst.end());
//
//			list<string> lst2 = resultSuchThat.second;
//			lst2.push_back(argTwo);
//			lst2.insert(lst2.end(), pkbResult.second.begin(), pkbResult.second.end());
//
//			resultSuchThat = make_pair(lst, lst2);
//			hasResult = true;
//		}
//	}
//	else
//	{
//		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
//	}
//}
//
//void QueryEvaluator::evaluatePattern(array<string, 6> arr)
//{
//    string argOneType = arr[0];
//    string argTwoType = arr[2];
//	string type3 = arr[4];
//    string argOne = arr[1];
//    string argTwo = arr[3];
//	string arg3 = arr[5];
//
//	// Case 1: pattern a(synonym, _)
//    if (argTwoType == "var" && type3 == UNDERSCORE)
//    {
//		pair<list<int>, list<string>> pkbResult = pkbInstance->getLeftVariables();
//
//		if (pkbResult.first.empty() && pkbResult.second.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
//			pkbResultFirst.push_front(argOne);
//
//			list<string> pkbResultSecond = pkbResult.second;
//			pkbResultSecond.push_front(argTwo);
//
//			resultPattern = make_pair(pkbResultFirst, pkbResultSecond);
//			hasResult = true;
//		}
//    }
//
//	// Case 2: pattern a(synonym, ident)
//	else if (argTwoType == "var" && type3 == "ident")
//	{
//		string ident = regex_replace(arg3, regex("\""), "");
//		ident = regex_replace(ident, regex(UNDERSCORE), "");
//		pair<list<int>, list<string>> pkbResult = pkbInstance->getLeftVariablesThatMatchWith(ident);
//
//		if (pkbResult.first.empty() && pkbResult.second.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			list<string> pkbResultFirst = getListStringFromListInt(pkbResult.first);
//			pkbResultFirst.push_front(argOne);
//
//			list<string> pkbResultSecond = pkbResult.second;
//			pkbResultSecond.push_front(argTwo);
//
//			resultPattern = make_pair(pkbResultFirst, pkbResultSecond);
//			hasResult = true;
//		}
//	}
//
//	// Case 3: pattern a(_, ident)
//    else if (argTwoType == UNDERSCORE && type3 == "ident")
//    {
//		string ident = regex_replace(arg3, regex("\""), "");
//		ident = regex_replace(ident, regex(UNDERSCORE), "");
//
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getPartialMatchStmt(ident));
//
//		if (pkbResult.empty())
//		{
//
//			hasResult = false;
//		}
//		else
//		{
//			pkbResult.push_front(argOne);
//			resultPattern.first = pkbResult;
//			hasResult = true;
//		}
//
//    }
//	// Case 4: pattern a(ident, ident)
//    else if (argTwoType == "ident" && type3 == "ident")
//    {
//
//		string ident1 = regex_replace(argTwo, regex("\""), "");
//		ident1 = regex_replace(ident1, regex(UNDERSCORE), "");
//
//		string ident2 = regex_replace(arg3, regex("\""), "");
//		ident2 = regex_replace(ident2, regex(UNDERSCORE), "");
//
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getPartialBothMatches(ident1, ident2));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			pkbResult.push_front(argOne);
//			resultPattern.first = pkbResult;
//			hasResult = true;
//		}
//    }
//
//	// Case 5: pattern a(_, _)
//    else if (argTwoType == UNDERSCORE && type3 == UNDERSCORE)
//    {
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getAllAssignments());
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			pkbResult.push_front(argOne);
//			resultPattern.first = pkbResult;
//			hasResult = true;
//		}
//    }
//
//	// Case 6: pattern a(ident, _)
//    else if (argTwoType == "ident" && type3 == UNDERSCORE)
//    {
//		string ident = regex_replace(argTwo, regex("\""), "");
//		ident = regex_replace(ident, regex(UNDERSCORE), "");
//
//		list<string> pkbResult = getListStringFromListInt(pkbInstance->getAllAssignments(ident));
//
//		if (pkbResult.empty())
//		{
//			hasResult = false;
//		}
//		else
//		{
//			pkbResult.push_front(argOne);
//			resultPattern.first = pkbResult;
//			hasResult = true;
//		}
//    }
//    else
//    {
//        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ", " << type3 << ":" << arg3 << ">" << endl;
//    }
//
//}
//
///*--------------- Evaluator helper methods ---------------*/
//
///*--------------- Find set intersection between two lists---------------*/
//list<string> QueryEvaluator::getIntersection(list<string> list1, list<string> list2)
//{
//    list<string> tempList1 = list1;
//    list<string> tempList2 = list2;
//
//    tempList1.pop_front();
//    tempList2.pop_front();
//    tempList1.sort();
//    tempList2.sort();
//
//    list<string> result;
//    set_intersection(tempList1.begin(), tempList1.end(), tempList2.begin(), tempList2.end(), back_inserter(result));
//    return result;
//}
//
//list<string> QueryEvaluator::getCommonSynonymResult(list<string> select, pair<list<string>, list<string>> suchThat, pair<list<string>, list<string>> pattern)
//{
//    list<string> tempResult = {};
//    list<string> tempResultSuchThat;
//    list<string> tempResultPattern;
//
//    if (select.empty())
//        return tempResult;
//
//    tempResultSuchThat = select;
//    tempResultPattern = select;
//
//    tempResultSuchThat.pop_front();
//    tempResultPattern.pop_front();
//    tempResultSuchThat.sort();
//    tempResultPattern.sort();
//
//    if (!suchThat.first.empty() || !suchThat.second.empty())
//    {
//        if (!suchThat.first.empty()) 
//        {
//            if (select.front() == suchThat.first.front()) {
//                tempResultSuchThat = getIntersection(select, suchThat.first);
//            }
//        }
//
//        if (!suchThat.second.empty())
//        {
//            if (select.front() == suchThat.second.front()) 
//            {
//                tempResultSuchThat = getIntersection(select, suchThat.second);
//            }
//        }
//    }
//
//    if (!pattern.first.empty() || !pattern.second.empty())
//    {
//        if (!pattern.first.empty())
//        {
//            if (select.front() == pattern.first.front()) 
//            {
//                tempResultPattern = getIntersection(select, pattern.first);
//            }
//        }
//
//        if (!pattern.second.empty())
//        {
//            if (select.front() == pattern.second.front())
//                tempResultPattern = getIntersection(select, pattern.second);
//        }
//    }
//
//    set_intersection(tempResultSuchThat.begin(), tempResultSuchThat.end(), tempResultPattern.begin(), tempResultPattern.end(), back_inserter(tempResult));
//    return tempResult;
//}
//
//list<string> QueryEvaluator::getListStringFromListInt(list<int> listOfInt)
//{
//    list<string> listOfString;
//    for (std::list<int>::iterator it = listOfInt.begin(); it != listOfInt.end(); ++it) {
//        string stringFromInt = to_string(*it);
//        listOfString.push_back(stringFromInt);
//    }
//    return listOfString;
//}
