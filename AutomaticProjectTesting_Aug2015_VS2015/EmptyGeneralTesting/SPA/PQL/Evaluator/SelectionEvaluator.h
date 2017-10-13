#pragma once
#include "../Utilities/SelectClause.h"
#include "../Utilities/ClauseResult.h"

class SelectionEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

	bool evaluate(SelectClause clause, ClauseResult* clauseResult);

private:
	list<int> singleSynonymSelectionResult;
	list<list<int>> tupleSelectionResults;
	bool hasValidSelection;

};

