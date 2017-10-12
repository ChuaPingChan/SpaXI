#pragma once

#include <string>
#include <set>
#include <list>
#include "QueryTree.h"

using namespace std;

class ResultFormatter
{
public:
	ResultFormatter();
	list<string> finalResult();
protected:
	list<string> resultsFromSelection(ClauseResult cr, QueryTree qt);
		
};

