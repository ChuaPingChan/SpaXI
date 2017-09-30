#pragma once
#include "../ClauseEvaluator.h"
#include "../../Utilities/PatternClause.h" 

class PatternEvaluator : public ClauseEvaluator
{
public:
	PatternEvaluator();
	~PatternEvaluator();

	virtual ClauseResult evaluate(PatternClause clause) = 0;
};

