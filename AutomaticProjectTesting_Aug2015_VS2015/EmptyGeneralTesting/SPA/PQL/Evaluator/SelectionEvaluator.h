#pragma once
#include "../Utilities/SelectClause.h"
#include "../Utilities/ClauseResult.h"

class SelectionEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

	ClauseResult evaluate(SelectClause clause);
};

