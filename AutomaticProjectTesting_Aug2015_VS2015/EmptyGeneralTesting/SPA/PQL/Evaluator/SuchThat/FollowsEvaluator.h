#pragma once
#include "SuchThatRelEvaluator.h"

class FollowsEvaluator : public SuchThatRelEvaluator
{
public:
	FollowsEvaluator();
	~FollowsEvaluator();

	ClauseResult evaluate(SuchThatClause stClause);

private:
	PKBMain* pkbInstance;
}; 

