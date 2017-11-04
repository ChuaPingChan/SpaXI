#pragma once
#include "../../Utilities/ClauseResult.h"
#include "../../Utilities/WithClause.h"
#include "../../../PKB/PKBMain.h"
#include "../../../Exceptions/UnrecognisedTypeException.h"

class WithEvaluator
{
public:
    WithEvaluator();
    ~WithEvaluator();

    virtual bool evaluate(WithClause stClause, ClauseResult * clauseResult) = 0;

protected:
    PKBMain* pkbInstance;
};

