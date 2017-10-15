#pragma once
#include "PatternEvaluator.h"

class WhilePatternEvaluator : public PatternEvaluator
{
public:
	WhilePatternEvaluator();
	~WhilePatternEvaluator();

	bool evaluate(PatternClause ptClause, ClauseResult* clauseResult);
};

