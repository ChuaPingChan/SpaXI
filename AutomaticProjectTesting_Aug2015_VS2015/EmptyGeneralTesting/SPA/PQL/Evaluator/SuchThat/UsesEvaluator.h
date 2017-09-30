#pragma once
#include "SuchThatRelEvaluator.h"

class UsesEvaluator
{
public:
	UsesEvaluator();
	~UsesEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

