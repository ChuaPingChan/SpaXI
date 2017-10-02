#pragma once
#include "../../Utilities/PatternClause.h"
#include "../../Utilities/ClauseResult.h"

class PatternEvaluator
{
public:
	PatternEvaluator();
	~PatternEvaluator();

	virtual ClauseResult evaluate(PatternClause clause) = 0;
};

