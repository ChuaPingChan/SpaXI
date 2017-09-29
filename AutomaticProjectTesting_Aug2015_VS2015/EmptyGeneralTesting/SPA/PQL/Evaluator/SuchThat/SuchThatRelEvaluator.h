#pragma once
#include "../ClauseEvaluator.h"
#include "../../Utilities/SuchThatClause.h"

class SuchThatRelEvaluator : public ClauseEvaluator
{
public:
	SuchThatRelEvaluator();
	~SuchThatRelEvaluator();

	virtual ClauseResult evaluate(SuchThatClause stClause) = 0;
};

