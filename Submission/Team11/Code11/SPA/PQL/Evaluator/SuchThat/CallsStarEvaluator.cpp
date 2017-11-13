#include "CallsStarEvaluator.h"



CallsStarEvaluator::CallsStarEvaluator()
{
}


CallsStarEvaluator::~CallsStarEvaluator()
{
}

bool CallsStarEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: Calls*(ident, ident)
    if (argOneType == IDENT_WITHQUOTES && argTwoType == IDENT_WITHQUOTES)
    {
        return pkbInstance->isCallsStar(argOne, argTwo);
    }

    //Case 2: Calls*(ident, _)
    else if (argOneType == IDENT_WITHQUOTES && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isCaller(argOne);
    }

    //Case 3: Calls*(ident, synonym)
    else if (argOneType == IDENT_WITHQUOTES && argTwoType == PROCEDURE)
    {
        list<int> pkbResult = pkbInstance->getCalleeStar(argOne);
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

    //Case 4: Calls*(_, ident)
    else if (argOneType == UNDERSCORE && argTwoType == IDENT_WITHQUOTES)
    {
        return pkbInstance->isCallee(argTwo);
    }

    //Case 5: Calls*(_, _)
    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
    {
        return pkbInstance->hasCalls();
    }

    //Case 6: Calls*(_, synonym)
    else if (argOneType == UNDERSCORE && argTwoType == PROCEDURE)
    {
        list<int> pkbResult = pkbInstance->getAllCallees();
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

    //Case 7: Calls*(synonym, ident)
    else if (argOneType == PROCEDURE && argTwoType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getCallerStar(argTwo);
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

    //Case 8: Calls*(synonym, _)
    else if (argOneType == PROCEDURE && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllCallers();
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

    //Case 9: Calls*(synonym, synonym)
    else if (argOneType == PROCEDURE && argTwoType == PROCEDURE)
    {
        // Checks if the two synonyms are already present in clauseResult
        bool argOneExists = clauseResult->synonymPresent(argOne);
        bool argTwoExists = clauseResult->synonymPresent(argTwo);

        if (argOneExists && argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getAllCallsStar();

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
            pair<list<int>, list<int>> pkbResult = pkbInstance->getAllCallsStar();

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

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getCalleeStar(existingSynVal);
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

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getCallerStar(existingSynVal);
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
        throw UnrecognisedTypeException("in CallsStarEvaluator. argOneType: " + to_string(argOneType) + ", argTwoType: " + to_string(argTwoType));
    }
}
