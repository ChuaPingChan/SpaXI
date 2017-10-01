#include "FollowsEvaluator.h"



FollowsEvaluator::FollowsEvaluator() : SuchThatRelEvaluator()
{
}


FollowsEvaluator::~FollowsEvaluator()
{
}

bool FollowsEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
	int argOneType = stClause.getArgOneType();
	int argTwoType = stClause.getArgTwoType();
	string argOne = stClause.getArgOne();
	string argTwo = stClause.getArgTwo();

	bool hasResult;

	//Case 1: Follows(int, int)
	if (argOneType == INTEGER && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isFollows(stoi(argOne), stoi(argTwo));
		return hasResult;
	}

	//Case 2: Follows(int, _)
	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->isBefore(stoi(argOne));
		return hasResult;
	}

	//Case 3: Follows(int, synonym)
	else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		bool exists = clauseResult->synonymPresent(argTwo);
		if (exists)
		{

		}
		else
		{
			list<int> result = pkbInstance->getAfter(stoi(argOne), argTwoType);
			//clauseResult->
		}
	}

	//Case 4: Follows(_, int)
	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
	{
		hasResult = pkbInstance->isAfter(stoi(argTwo));
	}

	//Case 5: Follows(_, _)
	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
	{
		hasResult = pkbInstance->hasFollows();
	}

	//Case 6: Follows(_, synonym)
	else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> result = pkbInstance->getAllAfter(argTwo);
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

	//Case 7: Follows(synonym, int)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == INTEGER)
	{
		list<int> result = pkbInstance->getBefore(stoi(argTwo), argOneType);
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

	//Case 8: Follows(synonym, _)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
	{
		list<int> result = pkbInstance->getAllBefore(argOneType);
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

	//Case 9: Follows(synonym, synonym)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		pair<list<int>, list<int>> result = pkbInstance->getAllFollows(argOneType, argTwoType);

		if (result.first.empty() && result.second.empty())
		{
			hasResult = false;
		}
		else
		{
			
			/*list<string> list1 = getListStringFromListInt(result.first);
			list<string> list2 = getListStringFromListInt(result.second);
			list1.push_front(argOne);
			list2.push_front(argTwo);
			resultSuchThat = make_pair(list1, list2);
			hasResult = true;*/
		}
	}
	else
	{
		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
	}

	return ClauseResult();
}
