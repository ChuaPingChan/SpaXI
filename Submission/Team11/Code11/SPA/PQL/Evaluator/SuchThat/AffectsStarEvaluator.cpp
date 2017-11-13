#include "AffectsStarEvaluator.h"



AffectsStarEvaluator::AffectsStarEvaluator()
{
}


AffectsStarEvaluator::~AffectsStarEvaluator()
{
}

bool AffectsStarEvaluator::evaluate(SuchThatClause stClause, ClauseResult * clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: AffectsStar(int, int)
    if (argOneType == INTEGER && argTwoType == INTEGER)
    {
        return pkbInstance->isAffectsStar(stoi(argOne), stoi(argTwo));
    }

    //Case 2: AffectsStar(int, _)
    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isAffector(stoi(argOne));
    }

    //Case 3: AffectsStar(int, synonym)
    else if (argOneType == INTEGER && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == PROG_LINE))
    {
        list<int> pkbResult = pkbInstance->getAffectedStarOf(stoi(argOne));
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

    //Case 4: Affects*(_, int)
    else if (argOneType == UNDERSCORE && argTwoType == INTEGER)
    {
        return pkbInstance->isAffected(stoi(argTwo));
    }

    //Case 5: Affects*(_, _)
    else if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
    {
        return pkbInstance->hasAffects();
    }

    //Case 6: Affects*(_, synonym)
    else if (argOneType == UNDERSCORE && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == PROG_LINE))
    {
        list<int> pkbResult = pkbInstance->getAllAffected();
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

    //Case 7: Affects*(synonym, int)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == PROG_LINE) && argTwoType == INTEGER)
    {
        list<int> pkbResult = pkbInstance->getAffectorStarOf(stoi(argTwo));
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

    //Case 8: Affects*(synonym, _)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == PROG_LINE) && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllAffector();
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

    //Case 9: Affects*(synonym, synonym)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == PROG_LINE) && (argTwoType == STMT || argTwoType == ASSIGN || argTwoType == PROG_LINE))
    {

        // Checks if the two synonyms are already present in clauseResult
        bool argOneExists = clauseResult->synonymPresent(argOne);
        bool argTwoExists = clauseResult->synonymPresent(argTwo);

        if (argOne == argTwo)
        {
            // Case when both synonym are the same
            list<int> pkbResult = pkbInstance->getAllAffectsStarSameSyn();
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

        else
        {
            if (argOneExists && argTwoExists)
            {

                pair<list<int>, list<int>> pkbResult = pkbInstance->getAllAffectsStar();

                if (pkbResult.first.empty() && pkbResult.second.empty())
                {
                    return false;
                } else
                {
                    // Both synonyms are new thus merging with existing results
                    clauseResult->updateSynPairResults(argOne, argTwo, pkbResult);
                    return clauseResult->hasResults();
                }
            }

            else if (!argOneExists && !argTwoExists)
            {

                pair<list<int>, list<int>> pkbResult = pkbInstance->getAllAffectsStar();

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
                        list<int> newSynVals = pkbInstance->getAffectedStarOf(existingSynVal);
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
                        list<int> newSynVals = pkbInstance->getAffectorStarOf(existingSynVal);
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
    }
    else
    {
        throw UnrecognisedTypeException("in AffectsStarEvaluator. argOneType: " + to_string(argOneType) + ", argTwoType: " + to_string(argTwoType));
    }
}


