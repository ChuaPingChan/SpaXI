#include "FollowsEvaluator.h"



FollowsEvaluator::FollowsEvaluator() : SuchThatRelEvaluator()
{
}


FollowsEvaluator::~FollowsEvaluator()
{
}

ClauseResult FollowsEvaluator::evaluate(SuchThatClause stClause)
{
	int argOneType = stClause.getArgOneType();
	int argTwoType = stClause.getArgTwoType();
	string argOne = stClause.getArgOne();
	string argTwo = stClause.getArgTwo();

	bool hasResult;

	////Case 1: Follows(int, int)
	//if (argOneType == "int" && argTwoType == "int")
	//{
	//	hasResult = pkbInstance->isFollows(stoi(argOne), stoi(argTwo));
	//}
	////Case 2: Follows(int, _)
	//else if (argOneType == "int" && argTwoType == "_")
	//{
	//	hasResult = pkbInstance->isBefore(stoi(argOne));
	//}
	////Case 3: Follows(int, synonym)
	//else if (argOneType == "int" && (argTwoType == "stmt" || argTwoType == "assign" || argTwoType == "while"))
	//{
	//	list<int> result = pkbInstance->getAfter(stoi(argOne), argTwoType);
	//	if (result.empty())
	//	{
	//		hasResult = false;
	//	}
	//	else
	//	{
	//		list<string> list1 = getListStringFromListInt(result);
	//		list<string> list2;
	//		list1.push_front(argTwo);
	//		resultSuchThat = make_pair(list1, list2);
	//		hasResult = true;
	//	}
	//}
	////Case 4: Follows(_, int)
	//else if (argOneType == "_" && argTwoType == "int")
	//{
	//	hasResult = pkbInstance->isAfter(stoi(argTwo));
	//}
	////Case 5: Follows(_, _)
	//else if (argOneType == "_" && argTwoType == "_")
	//{
	//	hasResult = pkbInstance->hasFollows();
	//}
	////Case 6: Follows(_, synonym)
	//else if (argOneType == "_" && (argTwoType == "stmt" || argTwoType == "assign" || argTwoType == "while"))
	//{
	//	list<int> result = pkbInstance->getAllAfter(argTwo);
	//	if (result.empty())
	//	{
	//		hasResult = false;
	//	}
	//	else
	//	{
	//		list<string> list1 = getListStringFromListInt(result);
	//		list<string> list2;
	//		list1.push_front(argTwo);
	//		resultSuchThat = make_pair(list1, list2);
	//		hasResult = true;
	//	}
	//}
	////Case 7: Follows(synonym, int)
	//else if ((argOneType == "stmt" || argOneType == "assign" || argOneType == "while") && argTwoType == "int")
	//{
	//	list<int> result = pkbInstance->getBefore(stoi(argTwo), argOneType);
	//	if (result.empty())
	//	{
	//		hasResult = false;
	//	}
	//	else
	//	{
	//		list<string> list1 = getListStringFromListInt(result);
	//		list<string> list2;
	//		list1.push_front(argOne);
	//		resultSuchThat = make_pair(list1, list2);
	//		hasResult = true;
	//	}
	//}
	////Case 8: Follows(synonym, _)
	//else if ((argOneType == "stmt" || argOneType == "assign" || argOneType == "while") && argTwoType == "_")
	//{
	//	list<int> result = pkbInstance->getAllBefore(argOneType);
	//	if (result.empty())
	//	{
	//		hasResult = false;
	//	}
	//	else
	//	{
	//		list<string> list1 = getListStringFromListInt(result);
	//		list<string> list2;
	//		list1.push_front(argOne);
	//		resultSuchThat = make_pair(list1, list2);
	//		hasResult = true;
	//	}
	//}
	////Case 9: Follows(synonym, synonym)
	//else if ((argOneType == "stmt" || argOneType == "assign" || argOneType == "while") && (argTwoType == "stmt" || argTwoType == "assign" || argTwoType == "while"))
	//{
	//	pair<list<int>, list<int>> result = pkbInstance->getAllFollows(argOneType, argTwoType);
	//	if (result.first.empty() && result.second.empty())
	//	{
	//		hasResult = false;
	//	}
	//	else
	//	{
	//		list<string> list1 = getListStringFromListInt(result.first);
	//		list<string> list2 = getListStringFromListInt(result.second);
	//		list1.push_front(argOne);
	//		list2.push_front(argTwo);
	//		resultSuchThat = make_pair(list1, list2);
	//		hasResult = true;
	//	}
	//}
	//else
	//{
	//	cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
	//}
}
