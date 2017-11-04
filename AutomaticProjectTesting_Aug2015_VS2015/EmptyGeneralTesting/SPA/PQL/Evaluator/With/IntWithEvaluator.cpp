#include "IntWithEvaluator.h"



IntWithEvaluator::IntWithEvaluator()
{
}


IntWithEvaluator::~IntWithEvaluator()
{
}

bool IntWithEvaluator::evaluate(WithClause wClause, ClauseResult * clauseResult)
{
    Entity leftHandSideType = wClause.getLhsEntity();
    Entity rightHandSideType = wClause.getRhsEntity();
    string leftHandSide = wClause.getLhsValue();
    string rightHandSide = wClause.getRhsValue();

    if (leftHandSideType == INTEGER && (rightHandSideType == STMT || rightHandSideType == ASSIGN || rightHandSideType == WHILE ||
        rightHandSideType == IF || rightHandSideType == CALL || rightHandSideType == CONSTANT || rightHandSideType == PROG_LINE))
    {
        if (pkbInstance->isInstanceOf(rightHandSideType, stoi(leftHandSide)))
        {
            clauseResult->updateSynResults(rightHandSide, list<int>{stoi(leftHandSide)});
            return clauseResult->hasResults();
        }
        else
        {
            return false;
        }
    }

    else if ((leftHandSideType == STMT || leftHandSideType == ASSIGN || leftHandSideType == WHILE ||
        leftHandSideType == IF || leftHandSideType == CALL || leftHandSideType == CONSTANT || leftHandSideType == PROG_LINE)
        && rightHandSideType == INTEGER)
    {
        if (pkbInstance->isInstanceOf(leftHandSideType, stoi(rightHandSide)))
        {
            clauseResult->updateSynResults(leftHandSide, list<int>{stoi(rightHandSide)});
            return clauseResult->hasResults();
        }
        else
        {
            return false;
        }
    }

    else if ((leftHandSideType == STMT || leftHandSideType == ASSIGN || leftHandSideType == WHILE ||
        leftHandSideType == IF || leftHandSideType == CALL || leftHandSideType == CONSTANT || leftHandSideType == PROG_LINE)
        && (rightHandSideType == STMT || rightHandSideType == ASSIGN || rightHandSideType == WHILE ||
            rightHandSideType == IF || rightHandSideType == CALL || rightHandSideType == CONSTANT || rightHandSideType == PROG_LINE))
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
                if (leftHandSideVal != rightHandSideVal)
                {
                    clauseResult->removeCombinations(leftHandSide, leftHandSideVal, rightHandSide, rightHandSideVal);
                }
            }

            return clauseResult->hasResults();
        }

        else if (!leftHandSideExists && !rightHandSideExists)
        {
            list<int> leftHandSideVals = pkbInstance->getAllIntOfIntEntity(leftHandSideType);
            list<int> rightHandSideVals = pkbInstance->getAllIntOfIntEntity(rightHandSideType);
            list<int> commonResult;

            for (int leftHandSideVal : leftHandSideVals)
            {
                for (int rightHandSideVal : rightHandSideVals)
                {
                    if (leftHandSideVal == rightHandSideVal)
                    {
                        commonResult.push_back(leftHandSideVal);
                    }
                }
            }

            if (commonResult.empty())
            {
                return false;
            }
            else
            {
                // Both synonyms are new thus merging with existing results
                clauseResult->addNewSynPairResults(leftHandSide, commonResult, rightHandSide, commonResult);
                return clauseResult->hasResults();
            }
        }

        else
        {
            string existingSyn;
            string newSyn;
            Entity newSynType;

            if (leftHandSideExists && !rightHandSideExists)
            {
                existingSyn = leftHandSide;
                newSyn = rightHandSide;
                newSynType = rightHandSideType;
            }
            else if (!leftHandSideExists && rightHandSideExists)
            {
                existingSyn = rightHandSide;
                newSyn = leftHandSide;
                newSynType = leftHandSideType;
            }

            // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
            list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
            list<int> newSynVals = pkbInstance->getAllIntOfIntEntity(newSynType);
            list<pair<int, int>> resultPairs;

            for (int existingSynVal : existingSynVals)
            {
                for (int newSynVal : newSynVals)
                {
                    if (existingSynVal == newSynVal)
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
        throw UnrecognisedTypeException("in IntWithEvaluator. leftHandSideType: " + to_string(leftHandSideType) + ", rightHandSideType: " + to_string(rightHandSideType));
    }
}
