#include "ResultFormatter.h"


using namespace std;

ResultFormatter::ResultFormatter()
{
    this->pkbInstance = PKBMain::getInstance();
}

list<string> ResultFormatter::finalResultFromSelection(ClauseResult cr, QueryTree qt)
{
	SelectClause selectionByQuery = qt.getSelectClause();
	list<string> selectSynonym;
	list<string> result;

	//Case 1: Select BOOLEAN
	if (selectionByQuery.getSelectionType()==SELECT_BOOLEAN)
	{
        bool isTreeEmpty = checkIfQueryTreeHasClauses(&qt);
		if (!cr.hasResults() && !isTreeEmpty) //If merging has finished and ClauseResult has no results, then BOOLEAN is false
		{
			result.push_back("false");
		}
		else 
		{
			result.push_back("true"); //If ClauseResult is empty, BOOLEAN is false
		}
	}
	
	//Case 2: Select synonym
	else if (selectionByQuery.getSelectionType() == SELECT_SINGLE)
	{
		if (cr.hasResults())
		{
			Entity argType = selectionByQuery.getSingleArgType();
            string synonymToGetResultFor = selectionByQuery.getSingleArg();

			if (argType == STMT || argType == ASSIGN || argType == WHILE || argType == IF || argType == PROG_LINE || argType == CALL || argType == CONSTANT || argType == STMTLIST)
			{
				result = convertListOfIntsToListOfStrings(cr.getSynonymResults(synonymToGetResultFor));
			}

            else if (argType == PROCEDURE || argType == VARIABLE)
            {
                result = pkbInstance->convertIdxToString(cr.getSynonymResults(synonymToGetResultFor), argType);
            }

        }
	
	}

	//Case 3: Select tuple
	else if (selectionByQuery.getSelectionType() == SELECT_TUPLE)
	{
      //To-Do
	}
	return result;
}

/******************
* Helper methods *
******************/
list<string> ResultFormatter::convertListOfIntsToListOfStrings(list<int> listOfInts)
{
	list<string> convertedFromInt;
	for (int i : listOfInts)
	{
		convertedFromInt.push_back(to_string(i));
	}
	
	return convertedFromInt;
}

list<string> ResultFormatter::convertListOfListOfIntsToListOfStrings(list<list<int>> listOfInts)
{
	list<string> convertedFromInt;
	return convertedFromInt;
}
bool ResultFormatter::checkIfQueryTreeHasClauses(QueryTree* qt)
{
    if (qt->getSuchThatClauses().empty() && qt->getPatternClauses().empty() && qt->getWithClauses().empty())
    {
        return true;
    }

    return false;
}


