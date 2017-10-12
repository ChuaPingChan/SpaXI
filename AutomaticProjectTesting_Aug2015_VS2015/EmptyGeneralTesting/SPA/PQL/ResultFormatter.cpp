#include "ResultFormatter.h"
#include "QueryTree.h"
#include "Utilities\ClauseResult.h"

using namespace std;

ResultFormatter::ResultFormatter()
{
}

list<string> ResultFormatter::finalResult()
{
	return list<string>();
}


/******************
* Helper methods *
******************/

list<string> ResultFormatter::resultsFromSelection(ClauseResult cr, QueryTree qt)
{
	SelectClause selectionByQuery = qt.getSelectClause();
	list<string> results;

	//Case 1: Select BOOLEAN
	if (selectionByQuery.getSelectionType()==SELECT_BOOLEAN)
	{
		if (!cr.getAllResults().empty())
		{
			results.push_back("TRUE");
		}
		else 
		{
			results.push_back("FALSE");
		}
	}
	//Case 2: Select Synnonym/Tuple

	return results;
}


