#pragma once

#include <string>
#include <set>
#include <list>
#include "..\QueryTree.h"
#include "..\Utilities\ClauseResult.h"

using namespace std;

class ResultFormatter
{

public:
	ResultFormatter();
	list<string> finalResultFromSelection(ClauseResult cr, QueryTree qt);

protected:
	list<string> convertListOfIntsToListOfStrings(list<int> listOfInts);
	list<string> convertListOfListOfIntsToListOfStrings(list<list<int>> listOfInts);
};
