#pragma once
#include "../Utilities/SelectClause.h"
#include "../Utilities/ClauseResult.h"
#include "../../Exceptions/UnrecognisedTypeException.h"
#include "../../PKB/PKBMain.h"
#include <stdio.h>

class SelectionEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

	bool evaluate(SelectClause clause, ClauseResult* clauseResult);

protected:
	list<int> evaluateSingleSynonymSelection(Entity argType, string synonym);
	PKBMain* pkbInstance;

private:
	list<int> singleSynonymSelectionResult;
	list<list<int>> tupleSelectionResults;
	bool hasResultForSelection;

};

