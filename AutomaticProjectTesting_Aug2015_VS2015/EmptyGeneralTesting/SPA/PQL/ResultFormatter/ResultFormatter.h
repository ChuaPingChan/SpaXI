#pragma once

#include <string>
#include <set>
#include <list>
#include <regex>
#include "..\QueryTree.h"
#include "..\Utilities\ClauseResult.h"
#include "..\..\PKB\PKBMain.h"

using namespace std;

class ResultFormatter
{

public:
	ResultFormatter();
	list<string> finalResultFromSelection(ClauseResult cr, QueryTree qt);
    list<string> handleNoResult(QueryTree qt);

protected:
	list<string> convertListOfIntsToListOfStrings(list<int> listOfInts);
	list<string> convertListOfListOfIntsToListOfStrings(list<list<int>> listOfInts);

private:
    PKBMain* pkbInstance;
};

