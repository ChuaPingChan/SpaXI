#pragma once
#include "../ClauseEvaluator.h"
#include "../../Utilities/SuchThatClause.h"

class SuchThatRelEvaluator : public ClauseEvaluator
{
public:
	SuchThatRelEvaluator();
	~SuchThatRelEvaluator();

	virtual bool evaluate(SuchThatClause stClause, ClauseResult * clauseResult) = 0;
};

