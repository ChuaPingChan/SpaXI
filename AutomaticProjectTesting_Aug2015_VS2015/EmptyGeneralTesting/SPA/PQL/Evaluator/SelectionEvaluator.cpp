#include "SelectionEvaluator.h"



SelectionEvaluator::SelectionEvaluator()
{
    this->pkbInstance = PKBMain::getInstance();
}


SelectionEvaluator::~SelectionEvaluator()
{
}
/*This class checks whether the select clause has a result or not. 
If it returns an empty Result for Select synonym or Select tuple, 
evaluation is stopped here*/
bool SelectionEvaluator::evaluate(SelectClause clause, ClauseResult* clauseResult)
{ 
    hasResultForSelection = false;
    list<int> resultsForOneSynonym;
    SelectionType selectionType = clause.getSelectionType();

    switch (selectionType)
    {

    case SELECT_BOOLEAN:
        {
            hasResultForSelection = true;
            break;
        }


    case SELECT_SINGLE:
        {
            resultsForOneSynonym = evaluateSingleSynonymSelection(clause.getSingleArgType(), clause.getSingleArg());
            if (!resultsForOneSynonym.empty()) //If Select synonym has results, proceed with evaluation
            {
                clauseResult->updateSynResults(clause.getSingleArg(), resultsForOneSynonym);
                hasResultForSelection = true;
            }
            break;
        }


    case SELECT_TUPLE:
    {
        vector<string> getAllSynonymsFromTuple = clause.getTupleArgs();
        vector<Entity> getAllEntititesFromTuple = clause.getTupleArgTypes();

        for (int i = 0; i < getAllSynonymsFromTuple.size(); i++)
        {
            string currentSynonym = getAllSynonymsFromTuple.at(i);
            Entity currentSynonymType = getAllEntititesFromTuple.at(i);
            resultsForOneSynonym = evaluateSingleSynonymSelection(currentSynonymType, currentSynonym);
            if (!resultsForOneSynonym.empty()) //If Select tuple has results for current synonym, proceed with evaluation
            {
                clauseResult->updateSynResults(currentSynonym, resultsForOneSynonym);
                hasResultForSelection = true;
            }
            else
            {
                hasResultForSelection = false; //Select synonym has no results for current synonym, break
                break;
            }
        }
        break;
    }

    default: hasResultForSelection = false; 
        break;
    }

    return hasResultForSelection;
}

list<int> SelectionEvaluator::evaluateSingleSynonymSelection(Entity argType, string synonym)
{
    if (argType == STMT)
    {
        return pkbInstance->getAllStatements();
    }
    else if (argType == ASSIGN)
    {
        return pkbInstance->getAllAssignments();

    }
    else if (argType == WHILE)
    {
        return pkbInstance->getAllWhiles();

    }
    else if (argType == IF)
    {
        return pkbInstance->getAllIfs();

    }
    else if (argType == PROG_LINE)
    {
        return pkbInstance->getAllStatements();

    }
    else if (argType == CALL)
    {
        return pkbInstance->getAllCallsStmt();

    }
    else if (argType == PROCEDURE)
    {
        return pkbInstance->getAllProcedures();

    }
    else if (argType == VARIABLE)
    {
        return pkbInstance->getAllVariables();

    }
    else if (argType == CONSTANT)
    {
        return pkbInstance->getAllConstants();

    }
    else if (argType == STMTLIST)
    {
        return pkbInstance->getStmtList();

    }
    else
    {
        cerr << "This is not a valid Entity!";
    }
}
