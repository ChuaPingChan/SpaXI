#include "AssignPatternEvaluator.h"



AssignPatternEvaluator::AssignPatternEvaluator()
{
}


AssignPatternEvaluator::~AssignPatternEvaluator()
{
}

bool AssignPatternEvaluator::evaluate(PatternClause ptClause, ClauseResult* clauseResult)
{
    Entity argOneType = ptClause.getArgOneType();
    Entity argTwoType = ptClause.getArgTwoType();
    string patternSyn = ptClause.getPatternSynonym();
    string argOne = ptClause.getArgOne();
    string argTwo = ptClause.getArgTwo();

    //Case 1: pattern a(_, _)
    if (argOneType == UNDERSCORE && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllAssignments();
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

    //Case 2: pattern a(_, _"expression"_)
    //TODO: Change EXPRESSION_SPEC to EXPRESSION_SPEC_PARTIAL
    else if (argOneType == UNDERSCORE && argTwoType == EXPRESSION_SPEC)
    {
        list<int> pkbResult = pkbInstance->getPartialMatchStmt(argTwo);
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

    //Case 3: pattern a(_, "expression")
    //TODO: Change EXPRESSION_SPEC to EXPRESSION_SPEC_EXACT
    else if (argOneType == UNDERSCORE && argTwoType == EXPRESSION_SPEC)
    {
        list<int> pkbResult = pkbInstance->getExactMatchStmt(argTwo);
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

    //Case 4: pattern a("x", _)
    if (argOneType == IDENT_WITHQUOTES && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getAllAssignments(argOne);
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

    //Case 5: pattern a("x", _"expression"_)
    //TODO: Change EXPRESSION_SPEC to EXPRESSION_SPEC_PARTIAL
    if (argOneType == IDENT_WITHQUOTES && argTwoType == EXPRESSION_SPEC)
    {
        list<int> pkbResult = pkbInstance->getPartialBothMatches(argOne, argTwo);
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

    //Case 6: pattern a("x", "expression")
    //TODO: Change EXPRESSION_SPEC to EXPRESSION_SPEC_EXACT
    if (argOneType == IDENT_WITHQUOTES && argTwoType == EXPRESSION_SPEC)
    {
        list<int> pkbResult = pkbInstance->getExactBothMatches(argOne, argTwo);
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

    //Case 7: pattern a(synonym, _)
    else if (argOneType == VARIABLE && argTwoType == UNDERSCORE)
    {
        // Checks if the two synonyms are already present in clauseResult
        bool patternSynExists = clauseResult->synonymPresent(patternSyn);
        bool variableExists = clauseResult->synonymPresent(argOne);

        if (patternSynExists && variableExists)
        {
            list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(patternSyn, argOne);

            for (pair<int, int> pair : resultPairs)
            {
                int patternSynVal = pair.first;
                int variableVal = pair.second;

                // Removes from clauseResult as it is no longer valid due to new relation
                if (!pkbInstance->isMod(patternSynVal, variableVal))
                {
                    clauseResult->removeCombinations(patternSyn, patternSynVal, argOne, variableVal);
                }
            }

            return clauseResult->hasResults();

        }

        else if (!patternSynExists && !variableExists)
        {
            pair<list<int>, list<int>> pkbResult = pkbInstance->getLeftVariables();

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
            if (patternSynExists && !variableExists)
            {
                string existingSyn = patternSyn;
                string newSyn = argOne;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                for (int existingSynVal : existingSynVals)
                {
                    //Get list of variables that are modified by the current assignment stmt (existingSynVal)
                    list<int> newSynVals = pkbInstance->getModifiesFromStmt(existingSynVal);
                    for (int newSynVal : newSynVals)
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
                clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);

                return clauseResult->hasResults();
            }

            else if (!patternSynExists && variableExists)
            {
                string existingSyn = argOne;
                string newSyn = patternSyn;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;

                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getAllAssignments(existingSynVal);
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
        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argOneType << ":" << argTwo << ", " << argTwoType << ":" << argTwo << ">" << endl;
    }

}
