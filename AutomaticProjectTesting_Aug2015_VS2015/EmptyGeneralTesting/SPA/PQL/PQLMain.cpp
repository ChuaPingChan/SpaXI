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
	QueryTree* qtInstance = QueryTree::getInstance();
	//qtInstance = qtInstance->clear();

	QueryValidator validator;
	bool isValid = validator.isValidQuery(query);

	if (isValid) 
	{
		QueryEvaluator evaluator;
		evaluator.evaluate();

		list<string> evaluatorResult = qtInstance->getEvaluatorResult();
		if (evaluatorResult.empty())
		{
			qtInstance = qtInstance->clear();
			return evaluatorResult;
		}
		else
		{
			ResultFormatter formatter;
			qtInstance = qtInstance->clear();
            return evaluatorResult;
		}
	}
	else
	{
		qtInstance = qtInstance->clear();
		return list<string>();
	}
}