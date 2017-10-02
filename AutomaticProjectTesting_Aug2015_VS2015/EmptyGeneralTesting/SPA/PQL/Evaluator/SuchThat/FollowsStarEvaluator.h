#pragma once
#include "SuchThatRelEvaluator.h"
#include "../../Utilities/SuchThatClause.h"

class FollowsStarEvaluator : public SuchThatRelEvaluator
{
public:
	FollowsStarEvaluator();
	~FollowsStarEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

