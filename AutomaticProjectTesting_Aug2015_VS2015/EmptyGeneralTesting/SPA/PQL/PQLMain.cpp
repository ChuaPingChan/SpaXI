#include "PQLMain.h"
#include <string>



PQLMain::PQLMain(string query)
{
    this->query = query;
}


PQLMain::~PQLMain()
{
}

list<string> PQLMain::run()
{

    QueryValidator validator = QueryValidator(&qt);
    bool isValid = validator.isValidQuery(query);
    list<string> finalResult;
    if (isValid)
    {
        QueryEvaluator evaluator(&qt);
        evaluator.evaluate();
        ClauseResult evaluatorResult = qt.getEvaluatorResult();
        ResultFormatter formatter;
        if (evaluator.hasResult())
        {          
            finalResult = formatter.finalResultFromSelection(evaluatorResult, qt);
        }
        
        else
        {
            finalResult = formatter.handleNoResult(evaluatorResult, qt);
        }
    }
    return finalResult;
}
