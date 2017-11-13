#pragma once
#include "SuchThatRelEvaluator.h"

class AffectsEvaluator : public SuchThatRelEvaluator
{
public:
    AffectsEvaluator();
    ~AffectsEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

