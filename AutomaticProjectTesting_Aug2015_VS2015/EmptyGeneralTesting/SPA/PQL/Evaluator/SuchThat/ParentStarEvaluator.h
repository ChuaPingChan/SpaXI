#pragma once
#include "SuchThatRelEvaluator.h"

class ParentStarEvaluator : public SuchThatRelEvaluator
{
public:
	ParentStarEvaluator();
	~ParentStarEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

