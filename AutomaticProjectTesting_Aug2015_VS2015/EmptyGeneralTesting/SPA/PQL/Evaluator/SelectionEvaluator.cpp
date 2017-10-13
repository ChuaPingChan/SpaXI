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
	list<int> resultsForSingleSynonym;
	//Case 1: Select BOOLEAN
	if (clause.getSelectionType() == SELECT_BOOLEAN)
	{
        hasResultForSelection = true;
        if(!clauseResult->hasResults() && clauseResult->isPopulated())
        hasResultForSelection = false;
	}

	//Case 2: Select synonym
	else if (clause.getSelectionType() == SELECT_SINGLE)
	{
		resultsForSingleSynonym = evaluateSingleSynonymSelection(clause.getSingleArgType(), clause.getSingleArg());
		if (!resultsForSingleSynonym.empty()) //If Select synonym has results, so proceed with evaluation
		{
			clauseResult->updateSynResults(clause.getSingleArg(), resultsForSingleSynonym);
			hasResultForSelection = true;
		}
	}

	//Case 3: Select <arg1,arg2>
	else if (clause.getSelectionType() == SELECT_TUPLE)
	{
		//To-Do
	}
	//cout << "Result for select evaluation is"<<hasResultForSelection;
	return hasResultForSelection;
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
		return list<int>();
		//return pkbInstance->getAllProgLines();

	}
	else if (argType == CALL)
	{
		return list<int>();
		//return pkbInstance->getAllCalls();

	}
	else if (argType == PROCEDURE)
	{
		return list<int>();
		//return pkbInstance->getALlProcedures();

	}
	else if (argType == VARIABLE)
	{
		return list<int>();
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
