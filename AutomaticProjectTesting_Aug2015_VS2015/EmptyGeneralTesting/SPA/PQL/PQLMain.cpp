#include "PQLMain.h"
#include <string>



PQLMain::PQLMain(string query)
{
    //TODO: Un-hack this
    string processedQuery = regex_replace(query, regex("prog_line"), "stmt");
    this->query = processedQuery;
}


PQLMain::~PQLMain()
{
}

list<string> PQLMain::run()
{

    QueryValidator validator = QueryValidator(&qt);
    bool isValid = validator.isValidQuery(query);

    /*if (isValid) 
    {
        QueryEvaluator evaluator;
        evaluator.evaluate();

        list<string> evaluatorResult = qt.getEvaluatorResult();
        if (evaluatorResult.empty())
        {
            return evaluatorResult;
        }
        else
        {
            ResultFormatter formatter;
            return evaluatorResult;
        }
    }
    else
    {
        return list<string>();
    }*/
    return list<string>();
}