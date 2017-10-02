#pragma once
#include "ClauseEvaluator.h"
#include "../Utilities/ClauseResult.h"
#include "../Utilities/SelectClause.h"

class SelectionEvaluator : public ClauseEvaluator
{
public:
	SelectionEvaluator();
	~SelectionEvaluator();

	ClauseResult evaluate(SelectClause clause);
};

