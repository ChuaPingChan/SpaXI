#include "IfPatternEvaluator.h"



IfPatternEvaluator::IfPatternEvaluator()
{
}


IfPatternEvaluator::~IfPatternEvaluator()
{
}

bool IfPatternEvaluator::evaluate(PatternClause ptClause, ClauseResult * clauseResult)
{
    Entity argOneType = ptClause.getArgOneType();
    string patternSyn = ptClause.getPatternSynonym();
    string argOne = ptClause.getArgOne();

    //Case 1: pattern i(_, _, _)
    if (argOneType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllIfs();
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

    //Case 2: pattern i(ident, _, _)
    else if (argOneType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getIfsWithControlVariable(argOne);
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

    //Case 3: pattern i(synonym, _, _)
    else if (argOneType == VARIABLE)
    {
        string controlVar = argOne;

        // Checks if the two synonyms are already present in clauseResult
        bool patternSynExists = clauseResult->synonymPresent(patternSyn);
        bool controlVarExists = clauseResult->synonymPresent(controlVar);

        //Case 3a
        if (patternSynExists && controlVarExists)
        {
            list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(patternSyn, argOne);

            for (pair<int, int> pair : resultPairs)
            {
                int patternSynVal = pair.first;
                int variableVal = pair.second;

                // Removed from clauseResult as it is no longer valid due to new relation
                if (!pkbInstance->isIfControlVar(patternSynVal, variableVal))
                {
                    clauseResult->removeCombinations(patternSyn, patternSynVal, argOne, variableVal);
                }
            }

            return clauseResult->hasResults();
        }

        //Case 3b
        else if (!patternSynExists && !controlVarExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getControlVariablesInIf();

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
                    list<int> newSynVals = pkbInstance->getControlVariablesInIf(existingSynVal);
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
                    list<int> newSynVals = pkbInstance->getIfFromControlVar(existingSynVal);
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
        throw UnrecognisedTypeException("in IfPatternEvaluator. argOneType: " + to_string(argOneType));
    }
}
