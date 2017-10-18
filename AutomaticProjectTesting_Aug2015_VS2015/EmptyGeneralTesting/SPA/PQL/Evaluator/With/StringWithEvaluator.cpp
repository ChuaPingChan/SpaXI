#include "StringWithEvaluator.h"



StringWithEvaluator::StringWithEvaluator()
{
}


StringWithEvaluator::~StringWithEvaluator()
{
}

bool StringWithEvaluator::evaluate(WithClause wClause, ClauseResult * clauseResult)
{
    Entity leftHandSideType = wClause.getLhsEntity();
    Entity rightHandSideType = wClause.getRhsEntity();
    string leftHandSide = wClause.getLhsValue();
    string rightHandSide = wClause.getRhsValue();

    if (leftHandSideType == IDENT_WITHQUOTES 
        && (rightHandSideType == PROCEDURE || rightHandSideType == CALL || rightHandSideType == VARIABLE))
    {
        if (pkbInstance->isInstanceOf(rightHandSideType, leftHandSide))
        {
            int rightHandSideIdx = pkbInstance->convertStringToIdx(leftHandSide, rightHandSideType);
            clauseResult->updateSynResults(rightHandSide, list<int>{rightHandSideIdx});
            return clauseResult->hasResults();
        }
        else
        {
            return false;
        }
    }

    else if ((leftHandSideType == PROCEDURE || leftHandSideType == CALL || leftHandSideType == VARIABLE)
        && rightHandSideType == IDENT_WITHQUOTES)
    {

        if (pkbInstance->isInstanceOf(leftHandSideType, rightHandSide))
        {
            int leftHandSideIdx = pkbInstance->convertStringToIdx(rightHandSide, leftHandSideType);
            clauseResult->updateSynResults(leftHandSide, list<int>{leftHandSideIdx});
            return clauseResult->hasResults();
        }
        else
        {
            return false;
        }
    }

    else if ((leftHandSideType == PROCEDURE || leftHandSideType == CALL || leftHandSideType == VARIABLE)
        && (rightHandSideType == PROCEDURE || rightHandSideType == CALL || rightHandSideType == VARIABLE))
    {
        // Checks if the two synonyms are already present in clauseResult
        bool leftHandSideExists = clauseResult->synonymPresent(leftHandSide);
        bool rightHandSideExists = clauseResult->synonymPresent(rightHandSide);

        if (leftHandSideExists && rightHandSideExists)
        {
            list<pair<int, int>> resultPairs = clauseResult->getSynonymPairResults(leftHandSide, rightHandSide);

            for (pair<int, int> pair : resultPairs)
            {
                int leftHandSideVal = pair.first;
                int rightHandSideVal = pair.second;

                // Removes from clauseResult as it is no longer valid due to new relation
                if (!pkbInstance->isSameName(leftHandSideType, leftHandSideVal, rightHandSideType, rightHandSideVal))
                {
                    clauseResult->removeCombinations(leftHandSide, leftHandSideVal, rightHandSide, rightHandSideVal);
                }
            }

            return clauseResult->hasResults();
        }

        else if (!leftHandSideExists && !rightHandSideExists)
        {
            list<int> leftHandSideVals = pkbInstance->getAllIdxOfStringEntity(leftHandSideType);
            list<int> rightHandSideVals = pkbInstance->getAllIdxOfStringEntity(rightHandSideType);
            list<int> leftNewResults;
            list<int> rightNewResults;
            
            for (int leftHandSideVal : leftHandSideVals)
            {
                for (int rightHandSideVal : rightHandSideVals)
                {
                    if (pkbInstance->isSameName(leftHandSideType, leftHandSideVal, rightHandSideType, rightHandSideVal))
                    {
                        leftNewResults.push_back(leftHandSideVal);
                        rightNewResults.push_back(rightHandSideVal);
                    }
                }
            }

            if (leftNewResults.empty() && rightNewResults.empty())
            {
                return false;
            }
            else
            {
                // Both synonyms are new thus merging with existing results
                clauseResult->addNewSynPairResults(leftHandSide, leftNewResults, rightHandSide, rightNewResults);
                return clauseResult->hasResults();
            }
        }

        else
        {
            string existingSyn;
            Entity existingSynType;
            string newSyn;
            Entity newSynType;

            if (leftHandSideExists && !rightHandSideExists)
            {
                existingSyn = leftHandSide;
                existingSynType = leftHandSideType;
                newSyn = rightHandSide;
                newSynType = rightHandSideType;
            }

            else if (!leftHandSideExists && rightHandSideExists)
            {
                existingSyn = rightHandSide;
                existingSynType = rightHandSideType;
                newSyn = leftHandSide;
                newSynType = leftHandSideType;
            }

            // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
            list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
            list<int> newSynVals = pkbInstance->getAllIdxOfStringEntity(newSynType);
            list<pair<int, int>> resultPairs;

            for (int existingSynVal : existingSynVals)
            {
                for (int newSynVal : newSynVals)
                {
                    if (pkbInstance->isSameName(existingSynType, existingSynVal, newSynType, newSynVal))
                    {
                        pair<int, int> resultPair(existingSynVal, newSynVal);
                        resultPairs.push_back(resultPair);
                    }
                }
            }

            clauseResult->pairWithOldSyn(existingSyn, newSyn, resultPairs);
            return clauseResult->hasResults();
        }
    }

    else
    {
        cerr << "Unrecognised type: <" << leftHandSideType << ":" << leftHandSide << ", " << rightHandSideType << ":" << rightHandSide << ">" << endl;
    }
}
