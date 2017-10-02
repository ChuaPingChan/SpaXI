#pragma once
#include "PatternEvaluator.h"

class AssignPatternEvaluator : public PatternEvaluator
{
public:
	AssignPatternEvaluator();
	~AssignPatternEvaluator();

	ClauseResult evaluate(PatternClause clause);
};

