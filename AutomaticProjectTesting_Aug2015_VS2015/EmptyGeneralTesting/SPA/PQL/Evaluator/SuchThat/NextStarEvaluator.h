#pragma once
#include "SuchThatRelEvaluator.h"

class NextStarEvaluator : public SuchThatRelEvaluator
{
public:
	NextStarEvaluator();
	~NextStarEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

