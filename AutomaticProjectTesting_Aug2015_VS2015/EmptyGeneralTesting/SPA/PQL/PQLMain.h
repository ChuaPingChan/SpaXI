#pragma once
#include <string>
#include <list>
#include "QueryTree.h"
#include "QueryValidator.h"
#include "QueryEvaluator.h"
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

