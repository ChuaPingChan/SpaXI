#pragma once
#include "PatternEvaluator.h"

class AssignPatternEvaluator : public PatternEvaluator
{
public:
	AssignPatternEvaluator();
	~AssignPatternEvaluator();

	bool evaluate(PatternClause ptClause, ClauseResult* clauseResult);
};

