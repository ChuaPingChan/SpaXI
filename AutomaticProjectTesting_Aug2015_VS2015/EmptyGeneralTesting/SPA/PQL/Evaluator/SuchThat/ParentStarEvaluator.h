#pragma once
#include "SuchThatRelEvaluator.h"

class ParentStarEvaluator : public SuchThatRelEvaluator
{
public:
	ParentStarEvaluator();
	~ParentStarEvaluator();

	bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

