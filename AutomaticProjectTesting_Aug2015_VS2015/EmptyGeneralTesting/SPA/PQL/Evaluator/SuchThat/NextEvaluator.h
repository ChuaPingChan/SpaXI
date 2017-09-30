#pragma once
#include "SuchThatRelEvaluator.h"

class NextEvaluator : public SuchThatRelEvaluator
{
public:
	NextEvaluator();
	~NextEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

