#pragma 
#include "SuchThatRelEvaluator.h"

class CallsEvaluator : public SuchThatRelEvaluator
{
public:
	CallsEvaluator();
	~CallsEvaluator();

	ClauseResult evaluate(SuchThatClause clause);
};

