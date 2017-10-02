#pragma once
#include <string>
#include <list>
#include "QueryTree.h"
#include "Validator\QueryValidator.h"
#include "Evaluator\QueryEvaluator.h"
#include "ResultFormatter.h"

using namespace std;

class PQLMain
{
public:
	PQLMain(string query);
	~PQLMain();

	list<string> run();

private:
	string query;
	QueryTree qt;
};

