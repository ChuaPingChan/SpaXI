#pragma once
#include "../../Utilities/PatternClause.h"
#include "../../Utilities/ClauseResult.h"
#include "../../../PKB/PKBMain.h"
#include "../../../Exceptions/UnrecognisedTypeException.h"


class PatternEvaluator
{
public:
    PatternEvaluator();
    ~PatternEvaluator();

    virtual bool evaluate(PatternClause ptClause, ClauseResult* clauseResult) = 0;

protected:
    PKBMain* pkbInstance;
};

