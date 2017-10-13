#include "SelectionEvaluator.h"



SelectionEvaluator::SelectionEvaluator()
{
}


SelectionEvaluator::~SelectionEvaluator()
{
}

bool SelectionEvaluator::evaluate(SelectClause clause, ClauseResult* clauseResult)
{ 
	hasValidSelection = false;
	
	if (clause.getSelectionType == SELECT_BOOLEAN && clauseResult->hasResults())
	{
		hasValidSelection = true;
	}
}
