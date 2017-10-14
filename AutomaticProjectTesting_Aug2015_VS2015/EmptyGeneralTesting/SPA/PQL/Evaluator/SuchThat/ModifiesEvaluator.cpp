#include "ModifiesEvaluator.h"



ModifiesEvaluator::ModifiesEvaluator() : SuchThatRelEvaluator()
{
}


ModifiesEvaluator::~ModifiesEvaluator()
{
}

bool ModifiesEvaluator::evaluate(SuchThatClause stClause, ClauseResult* clauseResult)
{
    Entity argOneType = stClause.getArgOneType();
    Entity argTwoType = stClause.getArgTwoType();
    string argOne = stClause.getArgOne();
    string argTwo = stClause.getArgTwo();

    //Case 1: Modifies(int, IDENT)
    if (argOneType == INTEGER && argTwoType == IDENT_WITHQUOTES)
    {
        return pkbInstance->isMod(stoi(argOne), argTwo);
    }

    //Case 2: Modifies(int, _)
    else if (argOneType == INTEGER && argTwoType == UNDERSCORE)
    {
        return pkbInstance->isModifyingAnything(stoi(argOne));
    }

    //Case 3: Modifies(int, synonym)
    else if (argOneType == INTEGER && (argTwoType == VARIABLE))
    {
        list<int> pkbResult = pkbInstance->getModifiesFromStmt(stoi(argOne));
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

    //Case 4: Modifies(synonym, IDENT)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL || argOneType == PROCEDURE)  && argTwoType == IDENT_WITHQUOTES)
    {
        list<int> pkbResult = pkbInstance->getModifiesFromVar(argTwo, argOneType);
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

    //Case 5: Modifies(synonym, _)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL || argOneType == PROCEDURE) && argTwoType == UNDERSCORE)
    {
        list<int> pkbResult = pkbInstance->getStmtThatModifiesAnything(argOneType);
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

 
    //Case 6: Modifies(synonym, synonym)
    else if ((argOneType == STMT || argOneType == ASSIGN || argOneType == WHILE || argOneType == IF || argOneType == PROG_LINE || argOneType == CALL || argOneType == PROCEDURE) && argTwoType == VARIABLE)
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
                if (!pkbInstance->isMod(argOneVal, argTwoVal)) 
                {
                    clauseResult->removeCombinations(argOne, argOneVal, argTwo, argTwoVal);
                }
            }

            return clauseResult->hasResults();

        }

        else if (!argOneExists && !argTwoExists)
        {
            //To-Do: Change API CALL
            pair<list<int>, list<int>> pkbResult = pkbInstance->getModifiesPairs(argOneType);

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
                Entity existingSynType = argOneType;
                string newSyn = argTwo;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getAfter(existingSynVal, existingSynType);
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
                Entity existingSynType = argTwoType;
                string newSyn = argOne;

                // Create a list of pairs of <existing syn res, new syn result> and pass it to ClauseResult to merge
                list<int> existingSynVals = clauseResult->getSynonymResults(existingSyn);
                list<pair<int, int>> resultPairs;
                resultPairs.clear();
                for (int existingSynVal : existingSynVals)
                {
                    list<int> newSynVals = pkbInstance->getBefore(existingSynVal, existingSynType);
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
        cerr << "Unrecognised type: <" << argOneType << ":" << argOne << ", " << argTwoType << ":" << argTwo << ">" << endl;
    }
}
