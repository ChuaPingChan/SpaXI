#pragma once
#include "SuchThatRelEvaluator.h"

class ParentEvaluator : public SuchThatRelEvaluator
{
public:
	ParentEvaluator();
	~ParentEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};
