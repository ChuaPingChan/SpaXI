#include "FollowsStarEvaluator.h"



FollowsStarEvaluator::FollowsStarEvaluator()
{
}


FollowsStarEvaluator::~FollowsStarEvaluator()
{
}

ClauseResult FollowsStarEvaluator::evaluate(SuchThatClause clause)
{

	int argOneType = clause.getArgOneType();
	int argTwoType = clause.getArgTwoType();
	string argOne = clause.getArgOne();
	string argTwo = clause.getArgTwo();

	bool hasResult;

	//Case 1: FollowsStar(int, int)
	if (argOneType == INTEGER && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isFollowsStar(stoi(argOne), stoi(argTwo));
	}
	//Case 2: FollowsStar(int, _)
	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->isBefore(stoi(argOne));
	}
	//Case 3: FollowsStar(int, synonym)
	else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> result = pkbInstance->getAfterStar(stoi(argOne), argTwoType);
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
	//Case 4: FollowsStar(_, int)
	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isAfter(stoi(argTwo));
	}
	//Case 5: FollowsStar(_, _)
	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->hasFollows();
	}
	//Case 6: FollowsStar(_, synonym)
	else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> result = pkbInstance->getAllAfterStar(argTwoType);
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
	//Case 7: FollowsStar(synonym, int)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == INTEGER)
	{
		list<int> result = pkbInstance->getBeforeStar(stoi(argTwo), argOneType);
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
	//Case 8: FollowsStar(synonym, _)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
	{
		list<int> result = pkbInstance->getAllBeforeStar(argOneType);
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
	//Case 9: FollowsStar(synonym, synonym)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		pair<list<int>, list<int>> result = pkbInstance->getAllFollowsStar(argOneType, argTwoType);
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
