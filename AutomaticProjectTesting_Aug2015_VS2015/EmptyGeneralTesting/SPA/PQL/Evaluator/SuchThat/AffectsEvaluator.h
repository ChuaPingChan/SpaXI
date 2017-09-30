#pragma once
#include "SuchThatRelEvaluator.h"

class AffectsEvaluator : public SuchThatRelEvaluator
{
public:
	AffectsEvaluator();
	~AffectsEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

