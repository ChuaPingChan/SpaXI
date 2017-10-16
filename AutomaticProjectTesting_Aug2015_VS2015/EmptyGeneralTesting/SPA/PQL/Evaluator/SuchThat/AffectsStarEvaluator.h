#pragma once
#include "SuchThatRelEvaluator.h"

class AffectsStarEvaluator : public SuchThatRelEvaluator
{
public:
	AffectsStarEvaluator();
	~AffectsStarEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

