#pragma 
#include "SuchThatRelEvaluator.h"

class CallsEvaluator : public SuchThatRelEvaluator
{
public:
    CallsEvaluator();
    ~CallsEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

