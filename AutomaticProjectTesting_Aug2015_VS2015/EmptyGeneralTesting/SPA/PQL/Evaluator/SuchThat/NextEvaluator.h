#pragma once
#include "SuchThatRelEvaluator.h"

class NextEvaluator : public SuchThatRelEvaluator
{
public:
	NextEvaluator();
	~NextEvaluator();

	bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

