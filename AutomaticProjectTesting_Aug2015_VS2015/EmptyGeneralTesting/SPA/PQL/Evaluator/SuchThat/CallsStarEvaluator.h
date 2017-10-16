#pragma once
#include "SuchThatRelEvaluator.h"

class CallsStarEvaluator : public SuchThatRelEvaluator
{
public:
    CallsStarEvaluator();
    ~CallsStarEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

