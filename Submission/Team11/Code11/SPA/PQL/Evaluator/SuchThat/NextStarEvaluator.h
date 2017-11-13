#pragma once
#include "SuchThatRelEvaluator.h"
#include "../../Utilities/SuchThatClause.h"

class NextStarEvaluator : public SuchThatRelEvaluator
{
public:
    NextStarEvaluator();
    ~NextStarEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);
};

