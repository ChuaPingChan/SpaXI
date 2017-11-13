#pragma once
#include "SuchThatRelEvaluator.h"

class AffectsStarEvaluator : public SuchThatRelEvaluator
{
public:
    AffectsStarEvaluator();
    ~AffectsStarEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

