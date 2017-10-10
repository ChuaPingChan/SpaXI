#pragma once
#include "SuchThatRelEvaluator.h"
#include "../../Utilities/SuchThatClause.h"

class FollowsStarEvaluator : public SuchThatRelEvaluator
{
public:
	FollowsStarEvaluator();
	~FollowsStarEvaluator();

	bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

