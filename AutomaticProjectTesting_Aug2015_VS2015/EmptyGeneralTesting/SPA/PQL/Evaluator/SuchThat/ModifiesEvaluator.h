#pragma once
#include "SuchThatRelEvaluator.h"

class ModifiesEvaluator : public SuchThatRelEvaluator
{
public:
    ModifiesEvaluator();
    ~ModifiesEvaluator();

    bool evaluate(SuchThatClause stClause, ClauseResult* clauseResult);

};

