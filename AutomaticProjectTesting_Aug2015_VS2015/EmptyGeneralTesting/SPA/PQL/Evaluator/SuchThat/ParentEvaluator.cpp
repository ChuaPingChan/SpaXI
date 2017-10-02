#include "ParentEvaluator.h"



ParentEvaluator::ParentEvaluator()
{
}


ParentEvaluator::~ParentEvaluator()
{
}

ClauseResult ParentEvaluator::evaluate(SuchThatClause clause)
{
	Entity argOneType = clause.getArgOneType();
	Entity argTwoType = clause.getArgTwoType();
	string argOne = clause.getArgOne();
	string argTwo = clause.getArgTwo();

	//Case 1: Parent(int, int)
	if (argOneType == INTEGER && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isParentChild(stoi(argOne), stoi(argTwo));
	}
	//Case 2: Parent(int, _)
	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->isParent(stoi(argOne));
	}
	//Case 3: Parent(int, synonym)
	else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> result = pkbInstance->getChildren(stoi(argOne), argTwoType);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> list1 = getListStringFromListInt(result);
			list<string> list2;
			list1.push_front(argTwo);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;
		}
	}
	//Case 4: Parent(_, int)
	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isChild(stoi(argTwo));
	}
	//Case 5: Parent(_, _)
	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->hasParentRel();
	}
	//Case 6: Parent(_, synonym)
	else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> result = pkbInstance->getAllChildren(argTwoType);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> list1 = getListStringFromListInt(result);
			list<string> list2;
			list1.push_front(argTwo);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;
		}
	}
	//Case 7: Parent(synonym, int)
	else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == INTEGER)
	{
		list<int> result = pkbInstance->getParent(stoi(argTwo), argOneType);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> list1 = getListStringFromListInt(result);
			list<string> list2;
			list1.push_front(argOne);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;
		}
	}
	//Case 8: Parent(synonym, _)
	else if ((argOneType == STMT || argOneType == WHILE) && argTwoType == UNDERSCORE)
	{
		list<int> result = pkbInstance->getAllParents(argOneType);
		if (result.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> list1 = getListStringFromListInt(result);
			list<string> list2;
			list1.push_front(argOne);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;
		}
	}
	//Case 9: Parent(synonym, synonym)
	else if ((argOneType == STMT || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		pair<list<int>, list<int>> result = pkbInstance->getAllParentsRel(argOneType, argTwoType);
		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
		else
		{
			list<string> list1 = getListStringFromListInt(result.first);
			list<string> list2 = getListStringFromListInt(result.second);
			list1.push_front(argOne);
			list2.push_front(argTwo);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;
		}
	}
	else
	{
		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
	}
}
