#include "NextEvaluator.h"



NextEvaluator::NextEvaluator()
{
}


NextEvaluator::~NextEvaluator()
{
}

bool NextEvaluator::evaluate(SuchThatClause stClause, ClauseResult * clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: Next(int, int)
    if (argOneType == INTEGER && argTwoType == INTEGER)
    {
        return pkbInstance->isNext(stoi(argOne), stoi(argTwo));
    }

    //Case 2: Next(int, _)
    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isExecutedBefore(stoi(argOne));
    }

    //Case 3: Next(int, synonym)
    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
    {
        list<int> pkbResult = pkbInstance->getExecutedAfter(stoi(argOne), argTwoType);

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

    //Case 4: Next(_, int)
    else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
    {
        return pkbInstance->isExecutedAfter(stoi(argTwo));
    }

    //Case 5: Next(_, _)
    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
    {
        return pkbInstance->hasNext();
    }

    //Case 6: Next(_, synonym)
    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
    {
        list<int> pkbResult = pkbInstance->getAllExecutedAfter(argTwoType);
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

    //Case 7: Next(synonym, int)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == INTEGER)
    {
        list<int> pkbResult = pkbInstance->getExecutedBefore(stoi(argTwo), argOneType);
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

    //Case 8: Next(synonym, _)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllExecutedBefore(argOneType);
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

    //Case 9: Next(synonym, synonym)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == WHILE || argTwoType == IF || argTwoType == PROG_LINE || argTwoType == CALL))
    {
        // Checks if the two synonyms are already present in clauseResult
        bool argOneExists = clauseResult->synonymPresent(argOne);
        bool argTwoExists = clauseResult->synonymPresent(argTwo);

        if (argOneExists && argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getAllNext(argOneType, argTwoType);

            if (pkbResult.first.empty() && pkbResult.second.empty())
            {
                return false;
            } else
            {
                // Merging with existing results
                clauseResult->updateSynPairResults(argOne, argTwo, pkbResult);
                return clauseResult->hasResults();
            }

        }

        else if (!argOneExists && !argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getAllNext(argOneType, argTwoType);

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
                string newSyn = argTwo;
                Entity newSynType = argTwoType;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getExecutedAfter(existingSynVal, newSynType);
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
                string newSyn = argOne;
                Entity newSynType = argOneType;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getExecutedBefore(existingSynVal, newSynType);
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
        throw UnrecognisedTypeException("in NextEvaluator. argOneType: " + to_string(argOneType) + ", argTwoType: " + to_string(argTwoType));
    }
}
