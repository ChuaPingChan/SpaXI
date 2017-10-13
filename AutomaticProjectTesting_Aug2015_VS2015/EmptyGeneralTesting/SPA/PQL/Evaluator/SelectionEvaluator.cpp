#include "SelectionEvaluator.h"



SelectionEvaluator::SelectionEvaluator()
{
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
	list<int> resultsForSingleSynonym;
	//Case 1: Select BOOLEAN
	if (clause.getSelectionType == SELECT_BOOLEAN)
	{
		hasResultForSelection = true;
	}

	//Case 2: Select synonym
	else if (clause.getSelectionType == SELECT_SINGLE)
	{
		resultsForSingleSynonym = evaluateSingleSynonymSelection(clause.getSingleArgType(), clause.getSingleArg());
		clauseResult->updateSynResults(clause.getSingleArg(), resultsForSingleSynonym);
	
	}

	//Case 3: Select <arg1,arg2>
	else if (clause.getSelectionType == SELECT_TUPLE)
	{
		//To-Do
	}
}

//To-Do: Fill in missing API after PKB is finished.
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
		//return pkbInstance->getAllProgLines();

	}
	else if (argType == CALL)
	{
		//return pkbInstance->getAllCalls();

	}
	else if (argType == PROCEDURE)
	{
		//return pkbInstance->getALlProcedures();

	}
	else if (argType == VARIABLE)
	{
		//return pkbInstance->getAllVariables();

	}
	else if (argType == CONSTANT)
	{
		return pkbInstance->getAllConstants();

	}
	else if (argType == STMTLIST)
	{
		return pkbInstance->getAllStatements();

	}
	else
	{
		cerr << "This is not a valid Entity!";
	}
}
