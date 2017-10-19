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
    ResultFormatter formatter;
    list<string> finalResult;
    if (isValid)
    {
        QueryEvaluator evaluator(&qt);
        evaluator.evaluate();
        ClauseResult evaluatorResult = qt.getEvaluatorResult();
        if (evaluator.hasResult())
        {          
            finalResult = formatter.finalResultFromSelection(evaluatorResult, qt);
        }

        else
        {
            finalResult = formatter.handleNoResult(qt);
        }
        
    }
    else 
    {
       finalResult = formatter.handleInvalidQuery(query);
                
    }
    return finalResult;
}
