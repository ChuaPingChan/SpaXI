#pragma once
#include "WithEvaluator.h"

class IntWithEvaluator : public WithEvaluator
{
public:
    IntWithEvaluator();
    ~IntWithEvaluator();

    bool evaluate(WithClause wClause, ClauseResult* clauseResult);
};

