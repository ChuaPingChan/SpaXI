#pragma once
#include "PatternEvaluator.h"

class IfPatternEvaluator : public PatternEvaluator
{
public:
	IfPatternEvaluator();
	~IfPatternEvaluator();

	bool evaluate(PatternClause ptClause, ClauseResult *clauseResult);
};

