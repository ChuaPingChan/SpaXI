#include "FollowsStarEvaluator.h"



FollowsStarEvaluator::FollowsStarEvaluator()
{
}


FollowsStarEvaluator::~FollowsStarEvaluator()
{
}

bool FollowsStarEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: Follows*(int, int)
    if (argOneType == INTEGER && argTwoType == INTEGER)
    {
        return pkbInstance->isFollowsStar(stoi(argOne), stoi(argTwo));
    }

    //Case 2: Follows*(int, _)
    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isBefore(stoi(argOne));
    }

    //Case 3: Follows*(int, synonym)
    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
    {
        list<int> pkbResult = pkbInstance->getAfterStar(stoi(argOne), argTwoType);
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(argTwo, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 4: Follows*(_, int)
    else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
    {
        return pkbInstance->isAfter(stoi(argTwo));
    }

    //Case 5: Follows*(_, _)
    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
    {
        return pkbInstance->hasFollows();
    }

    //Case 6: Follows*(_, synonym)
    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
    {
        list<int> pkbResult = pkbInstance->getAllAfter(argTwoType);
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(argTwo, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 7: Follows*(synonym, int)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == INTEGER)
    {
        list<int> pkbResult = pkbInstance->getBeforeStar(stoi(argTwo), argOneType);
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(argOne, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 8: Follows*(synonym, _)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllBeforeStar(argOneType);
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(argOne, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 9: Follows*(synonym, synonym)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
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
                if (!pkbInstance->isFollowsStar(argOneVal, argTwoVal))
                {
                    clauseResult->removeCombinations(argOne, argOneVal, argTwo, argTwoVal);
                }
            }

            return clauseResult->hasResults();

        }

        else if (!argOneExists && !argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getAllFollowsStar(argOneType, argTwoType);

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
                string existingSyn = argOne;
                Entity existingSynType = argOneType;
                string newSyn = argTwo;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getAfterStar(existingSynVal, existingSynType);
                    for (int newSynVal : newSynVals)
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
                clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);

                return clauseResult->hasResults();
            }

            else if (!argOneExists && argTwoExists)
            {
                string existingSyn = argTwo;
                Entity existingSynType = argTwoType;
                string newSyn = argOne;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getBeforeStar(existingSynVal, existingSynType);
                    for (int newSynVal : newSynVals)
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
                clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);

                return clauseResult->hasResults();
            }
        }
    }
    else
    {
        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
    }
}
