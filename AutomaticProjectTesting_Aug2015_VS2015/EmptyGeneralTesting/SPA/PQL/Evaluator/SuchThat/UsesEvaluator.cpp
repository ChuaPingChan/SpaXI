#include "UsesEvaluator.h"



UsesEvaluator::UsesEvaluator()
{
}


UsesEvaluator::~UsesEvaluator()
{
}

bool UsesEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: Uses(int, IDENT)
    if (argOneType == INTEGER && argTwoType == IDENT_WITHQUOTES)
    {
        return pkbInstance->isUses(stoi(argOne), argTwo);
    }

    //Case 2: Uses(int, _)
    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isUsingAnything(stoi(argOne));
    }

    //Case 3: Uses(int, synonym)
    else if (argOneType == INTEGER && (argTwoType == VARIABLE))
    {
        list<int> pkbResult = pkbInstance->getUsesFromStmt(stoi(argOne));
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

    //Case 4: Uses(synonym, IDENT)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getUsesFromVar(argTwo, argOneType);
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

    //Case 5: Uses(synonym, _)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getStmtThatUsesAnything(argOneType);
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


    //Case 6: Uses(synonym, synonym)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL) && argTwoType == VARIABLE)
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
                if (!pkbInstance->isUses(argOneVal, argTwoVal))
                {
                    clauseResult->removeCombinations(argOne, argOneVal, argTwo, argTwoVal);
                }
            }

            return clauseResult->hasResults();

        }

        else if (!argOneExists && !argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getUsesPairs(argOneType);

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
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getUsesFromStmt(existingSynVal);
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

                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getUsesFromVar(existingSynVal, newSynType);
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

    //Case 7: Uses(ident, ident)
    if (argOneType == IDENT_WITHQUOTES && argTwoType == IDENT_WITHQUOTES)
    {
        return pkbInstance->isUsesProc(argOne, argTwo);
    }

    //Case 8: Uses(ident, _)
    else if (argOneType == IDENT_WITHQUOTES && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isUsingAnythingProc(argOne);
    }

    //Case 9: Uses(ident, synonym)
    else if (argOneType == IDENT_WITHQUOTES && argTwoType == VARIABLE)
    {
        list<int> pkbResult = pkbInstance->getUsesFromProc(argOne);
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

    //Case 10: Uses(synonym, IDENT)
    else if (argOneType == PROCEDURE && argTwoType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getProcUsesFromVar(argTwo);
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

    //Case 11: Uses(synonym, _)
    else if (argOneType == PROCEDURE && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getProcThatUsesAnything();
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


    //Case 12: Uses(synonym, synonym)
    else if (argOneType == PROCEDURE && argTwoType == VARIABLE)
    {
        // Checks if the two synonyms are already present in clauseResult
        bool argOneExists = clauseResult->synonymPresent(argOne);
        bool argTwoExists = clauseResult->synonymPresent(argTwo);

        //Case 12a
        if (argOneExists && argTwoExists)
        {
            list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(argOne, argTwo);

            for (pair<int, int> pair : resultPairs)
            {
                int argOneVal = pair.first;
                int argTwoVal = pair.second;

                // Removes from clauseResult as it is no longer valid due to new relation
                if (!pkbInstance->isUsesProc(argOneVal, argTwoVal))
                {
                    clauseResult->removeCombinations(argOne, argOneVal, argTwo, argTwoVal);
                }
            }

            return clauseResult->hasResults();

        }

        //Case 12b
        else if (!argOneExists && !argTwoExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getProcUsesPair();

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
            //Case 12c
            if (argOneExists && !argTwoExists)
            {
                string existingSyn = argOne;
                string newSyn = argTwo;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getUsesFromProc(existingSynVal);
                    for (int newSynVal : newSynVals)
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
                clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);

                return clauseResult->hasResults();
            }

            //Case 12d
            else if (!argOneExists && argTwoExists)
            {
                string existingSyn = argTwo;
                string newSyn = argOne;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getProcUsesFromVar(existingSynVal);
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
        throw UnrecognisedTypeException("in UsesEvaluator. argOneType: " + to_string(argOneType) + ", argTwoType: " + to_string(argTwoType));
    }
}