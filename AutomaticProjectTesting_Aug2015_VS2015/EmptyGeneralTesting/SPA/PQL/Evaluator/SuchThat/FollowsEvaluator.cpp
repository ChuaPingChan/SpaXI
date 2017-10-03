#include "FollowsEvaluator.h"



FollowsEvaluator::FollowsEvaluator() : SuchThatRelEvaluator()
{
}


FollowsEvaluator::~FollowsEvaluator()
{
}

bool FollowsEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
	Entity argOneType = stClause.getArgOneType();
	Entity argTwoType = stClause.getArgTwoType();
	string argOne = stClause.getArgOne();
	string argTwo = stClause.getArgTwo();

	bool hasResult;

	//Case 1: Follows(int, int)
	if (argOneType == INTEGER && argTwoType == INTEGER)
	{
		return pkbInstance->isFollows(stoi(argOne), stoi(argTwo));
	}

	//Case 2: Follows(int, _)
	else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
	{
		return pkbInstance->isBefore(stoi(argOne));
	}

	//Case 3: Follows(int, synonym)
	else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> pkbResult = pkbInstance->getAfter(stoi(argOne), argTwoType);
		if (pkbResult.empty())
		{
			return false;
		}
		else
		{
			clauseResult->addNewSynResults(argOne, pkbResult);
			return clauseResult->hasResults();
		}
	}

	//Case 4: Follows(_, int)
	else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
	{
		return pkbInstance->isAfter(stoi(argTwo));
	}

	//Case 5: Follows(_, _)
	else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
	{
		return pkbInstance->hasFollows();
	}

	//Case 6: Follows(_, synonym)
	else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		list<int> pkbResult = pkbInstance->getAllAfter(argTwoType);
		if (pkbResult.empty())
		{
			return false;
		}
		else
		{
			clauseResult->addNewSynResults(argOne, pkbResult);
			return clauseResult->hasResults();
		}
	}

	//Case 7: Follows(synonym, int)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == INTEGER)
	{
		list<int> pkbResult = pkbInstance->getBefore(stoi(argTwo), argOneType);
		if (pkbResult.empty())
		{
			return false;
		}
		else
		{
			clauseResult->addNewSynResults(argOne, pkbResult);
			return clauseResult->hasResults();
		}
	}

	//Case 8: Follows(synonym, _)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && argTwoType == UNDERSCORE)
	{
		list<int> pkbResult = pkbInstance->getAllBefore(argOneType);
		if (pkbResult.empty())
		{
			return false;
		}
		else
		{
			clauseResult->addNewSynResults(argOne, pkbResult);
			return clauseResult->hasResults();
		}
	}

	//Case 9: Follows(synonym, synonym)
	else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE))
	{
		// Checks if the two synonyms are already present in clauseResult
		bool argOneExists = clauseResult->synonymPresent(argOne);
		bool argTwoExists = clauseResult->synonymPresent(argTwo);

		if (argOneExists && argTwoExists)
		{
			list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(argOne, argTwo);

			for (pair<int, int> pair : resultPairs)
			{
				int argOneVal = pair.first;
				int argTwoVal = pair.second;

				// Removes from clauseResult as it is no longer valid due to new relation
				if (!pkbInstance->isFollows(argOneVal, argTwoVal))
				{
					clauseResult->removeCombinations(argOne, argOneVal, argTwo, argTwoVal);
				}
			}

			return clauseResult->hasResults();
			
		}

		else if (!argOneExists && !argTwoExists)
		{
			pair<list<int>, list<int>> pkbResult = pkbInstance->getAllFollows(argOneType, argTwoType);

			if (pkbResult.first.empty() && pkbResult.second.empty())
			{
				return false;
			}
			else
			{
				// Both synonyms are new thus merging with existing results
				clauseResult->addNewSynPairResults(argOne, pkbResult.first, argTwo, pkbResult.second);
				return clauseResult->hasResults();
			}
		}

		else
		{
			if (argOneExists && !argTwoExists)
			{
				list<int> existingVals = clauseResult->getSynonymResults(argOne);

				for (int i : existingVals)
				{
					// Removes if it is no longer valid, else adding new synonym to existing result
					list<int> argTwoVals = pkbInstance->getAfter(i, argOneType);
					if (argTwoVals.empty())
					{
						clauseResult->removeCombinations(argOne, i);
					}
					else
					{
						clauseResult->pairWithOldSyn(argOne, i, argTwo, argTwoVals);
					}
				}

				return clauseResult->hasResults();
			}

			else if (!argOneExists && argTwoExists)
			{
				list<int> existingVals = clauseResult->getSynonymResults(argTwo);

				for (int i : existingVals)
				{
					// Removes if it is no longer valid, else adding new synonym to existing result
					list<int> argOneVals = pkbInstance->getBefore(i, argTwoType);
					if (argOneVals.empty())
					{
						clauseResult->removeCombinations(argTwo, i);
					}
					else
					{
						clauseResult->pairWithOldSyn(argTwo, i, argOne, argOneVals);
					}
				}

				return clauseResult->hasResults();
			}
		}
	}
	else
	{
		cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
	}
}