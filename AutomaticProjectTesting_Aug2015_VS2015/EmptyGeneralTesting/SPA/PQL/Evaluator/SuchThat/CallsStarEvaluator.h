#pragma once
#include "SuchThatRelEvaluator.h"

class CallsStarEvaluator : public SuchThatRelEvaluator
{
public:
	CallsStarEvaluator();
	~CallsStarEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};
