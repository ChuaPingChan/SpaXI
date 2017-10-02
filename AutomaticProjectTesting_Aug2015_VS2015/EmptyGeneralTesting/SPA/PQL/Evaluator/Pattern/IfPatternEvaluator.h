#pragma once
#include "PatternEvaluator.h"

class IfPatternEvaluator : public PatternEvaluator
{
public:
	IfPatternEvaluator();
	~IfPatternEvaluator();

	ClauseResult evaluate(PatternClause clause);
};

