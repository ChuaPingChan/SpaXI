#include "WhilePatternEvaluator.h"



WhilePatternEvaluator::WhilePatternEvaluator()
{
}


WhilePatternEvaluator::~WhilePatternEvaluator()
{
}

bool WhilePatternEvaluator::evaluate(PatternClause ptClause, ClauseResult * clauseResult)
{
    Entity argOneType = ptClause.getArgOneType();
    string patternSyn = ptClause.getPatternSynonym();
    string argOne = ptClause.getArgOne();

    //Case 1: pattern w(_, _)
    if (argOneType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllWhiles();
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(patternSyn, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 2: pattern w(ident, _)
    else if (argOneType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getWhilesWithControlVariable(argOne);
        if (pkbResult.empty())
        {
            return false;
        }
        else
        {
            clauseResult->updateSynResults(patternSyn, pkbResult);
            return clauseResult->hasResults();
        }
    }

    //Case 3: pattern w(synonym, _)
    else if (argOneType == VARIABLE)
    {
        string controlVar = argOne;

        // Checks if the two synonyms are already present in clauseResult
        bool patternSynExists = clauseResult->synonymPresent(patternSyn);
        bool controlVarExists = clauseResult->synonymPresent(controlVar);

        //Case 3a
        if (patternSynExists && controlVarExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getControlVariablesInWhile();

            if (pkbResult.first.empty() && pkbResult.second.empty())
            {
                return false;
            } else
            {
                // Merging with existing results
                clauseResult->updateSynPairResults(patternSyn, argOne, pkbResult);
                return clauseResult->hasResults();
            }
        }

        //Case 3b
        else if (!patternSynExists && !controlVarExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getControlVariablesInWhile();

            if (pkbResult.first.empty() && pkbResult.second.empty())
            {
                return false;
            }
            else
            {
                // Both synonyms are new thus merging with existing results
                clauseResult->addNewSynPairResults(patternSyn, pkbResult.first, argOne, pkbResult.second);
                return clauseResult->hasResults();
            }
        }

        else
        {
            //Case 3c
            if (patternSynExists && !controlVarExists)
            {
                string existingSyn = patternSyn;
                string newSyn = argOne;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getControlVariablesInWhile(existingSynVal);
                    for (int newSynVal : newSynVals)
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
                clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);

                return clauseResult->hasResults();
            }

            //Case 3d
            else if (!patternSynExists && controlVarExists)
            {
                string existingSyn = argOne;
                string newSyn = patternSyn;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                // For every value of the existing synonym, get the values of the new synonym that satisfy the new relation
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getWhileFromControlVar(existingSynVal);
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
        throw UnrecognisedTypeException("in WhilePatternEvaluator. argOneType: " + to_string(argOneType));
    }
}
