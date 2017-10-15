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

    //Case 1: pattern w(_, _)
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

    //Case 2: pattern w(ident, _)
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
            list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(patternSyn, argOne);

            for (pair<int, int> pair : resultPairs)
            {
                int patternSynVal = pair.first;
                int variableVal = pair.second;

                // Removes from clauseResult as it is no longer valid due to new relation
                if (!pkbInstance->isExactMatch(patternSynVal, variableVal))
                {
                    clauseResult->removeCombinations(patternSyn, patternSynVal, argOne, variableVal);
                }
            }

            return clauseResult->hasResults();
        }

        //Case 3b
        else if (!patternSynExists && !controlVarExists)
        {

        }

        else
        {
            //Case 3c
            if (!patternSynExists && !controlVarExists)
            {

            }

            //Case 3d
            else if (!patternSynExists && !controlVarExists)
            {

            }
        }
    }
}
