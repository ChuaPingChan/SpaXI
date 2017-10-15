#pragma once
#include "WithEvaluator.h"

class StringWithEvaluator : public WithEvaluator
{
public:
    StringWithEvaluator();
    ~StringWithEvaluator();

    bool evaluate(WithClause wClause, ClauseResult* clauseResult);
};

