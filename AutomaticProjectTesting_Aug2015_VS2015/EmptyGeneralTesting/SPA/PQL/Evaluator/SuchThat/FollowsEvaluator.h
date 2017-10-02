#pragma once
#include "SuchThatRelEvaluator.h"

class FollowsEvaluator : public SuchThatRelEvaluator
{
public:
	FollowsEvaluator();
	~FollowsEvaluator();

	bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);

}; 

