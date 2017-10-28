#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator(QueryTree* qtPtr)
{
    this->_qt = qtPtr;
    hasResultEvaluator = true;
}

QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
    ResultFactory factory = ResultFactory();

    for (SuchThatClause stClause : _qt->getSuchThatClauses())
    {
        hasResultEvaluator = factory.processClause(stClause);
        if (!hasResultEvaluator)
            break;
    }

    if (hasResultEvaluator)
    {
        for (PatternClause ptClause : _qt->getPatternClauses())
        {
            hasResultEvaluator = factory.processClause(ptClause);
            if (!hasResultEvaluator)
                break;
        }
    }

    if (hasResultEvaluator)
    {
        for (WithClause wClause : _qt->getWithClauses())
        {
            hasResultEvaluator = factory.processClause(wClause);
            if (!hasResultEvaluator)
                break;
        }
    }

    if (hasResultEvaluator)
    {
        SelectClause slClause = _qt->getSelectClause();
        hasResultEvaluator = factory.processClause(slClause);
    }

    if (hasResultEvaluator)
    {
        _qt->storeEvaluatorResult(factory.makeClauseResult());
    }
}

bool QueryEvaluator::hasResult()
{
    return hasResultEvaluator;
}
