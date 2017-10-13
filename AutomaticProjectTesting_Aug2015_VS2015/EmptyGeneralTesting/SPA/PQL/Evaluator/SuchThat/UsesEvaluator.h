#pragma once
#include "SuchThatRelEvaluator.h"

class UsesEvaluator : public SuchThatRelEvaluator
{
public:
    UsesEvaluator();
    ~UsesEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};