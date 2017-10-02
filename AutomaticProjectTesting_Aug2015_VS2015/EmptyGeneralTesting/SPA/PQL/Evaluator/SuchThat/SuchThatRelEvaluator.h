#pragma once
#include "../../Utilities/ClauseResult.h"
#include "../../Utilities/SuchThatClause.h"
#include "../../../PKB/PKBMain.h"

class SuchThatRelEvaluator
{
public:
    SuchThatRelEvaluator();
    ~SuchThatRelEvaluator();

    virtual bool evaluate(SuchThatClause stClause, ClauseResult * clauseResult) = 0;

protected:
    PKBMain* pkbInstance;
};

