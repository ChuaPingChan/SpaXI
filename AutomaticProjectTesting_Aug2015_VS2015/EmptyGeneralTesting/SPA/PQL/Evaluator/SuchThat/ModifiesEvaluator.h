#pragma once
#include "SuchThatRelEvaluator.h"

class ModifiesEvaluator : public SuchThatRelEvaluator
{
public:
	ModifiesEvaluator();
	~ModifiesEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

