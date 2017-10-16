#pragma once
#include "SuchThatRelEvaluator.h"

class ParentEvaluator : public SuchThatRelEvaluator
{
public:
	ParentEvaluator();
	~ParentEvaluator();

	bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

