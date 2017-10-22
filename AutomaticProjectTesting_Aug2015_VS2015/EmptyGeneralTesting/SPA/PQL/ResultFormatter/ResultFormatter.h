#pragma once

#include <string>
#include <set>
#include <list>
#include <regex>
#include <algorithm>
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
    string convertListOfStringsToSingleString(list<string> singleSynResult);
    list<string> handleSelectBoolean(ClauseResult cr);
    list<string> handleSelectSynonym(ClauseResult cr, SelectClause sc);
    list<string> handleSelectTuple(ClauseResult cr, SelectClause selectedClause);

private:
    PKBMain* pkbInstance;
};

