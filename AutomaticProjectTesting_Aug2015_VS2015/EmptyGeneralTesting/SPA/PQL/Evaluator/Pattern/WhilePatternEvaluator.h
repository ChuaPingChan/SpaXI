#pragma once
#include "PatternEvaluator.h"

class WhilePatternEvaluator : public PatternEvaluator
{
public:
	WhilePatternEvaluator();
	~WhilePatternEvaluator();

	ClauseResult evaluate(PatternClause clause);
};

