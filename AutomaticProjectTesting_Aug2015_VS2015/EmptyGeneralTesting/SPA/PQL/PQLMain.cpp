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
	validator.isValidQuery(query);

	QueryEvaluator evaluator;
	evaluator.evaluate();


}

