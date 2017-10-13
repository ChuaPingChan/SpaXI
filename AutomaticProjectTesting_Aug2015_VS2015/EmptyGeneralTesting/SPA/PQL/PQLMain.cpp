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

    if (isValid)
    {
        QueryEvaluator evaluator(&qt);
        evaluator.evaluate();
        ClauseResult evaluatorResult = qt.getEvaluatorResult();
		 if (evaluatorResult.hasResults()) {
            ResultFormatter formatter;
            return formatter.finalResultFromSelection(evaluatorResult, qt);
        }
		 return list<string>();
    }
    else
    {
        return list<string>();
    }
}
