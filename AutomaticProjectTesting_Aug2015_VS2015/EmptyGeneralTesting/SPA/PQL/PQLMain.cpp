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
	QueryTree* qtInstance = QueryTree::getInstance();

	QueryValidator validator;
	bool isValid = validator.isValidQuery(query);

	if (isValid) 
	{
		QueryEvaluator evaluator;
		evaluator.evaluate();

		list<string> evaluatorResult = qtInstance->getEvaluatorResult();
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
	}


}