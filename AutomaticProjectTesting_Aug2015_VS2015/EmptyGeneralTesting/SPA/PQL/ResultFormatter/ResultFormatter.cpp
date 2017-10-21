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
    SelectionType selectedType = selectionByQuery.getSelectionType();
    switch (selectedType)
    {
    case SELECT_BOOLEAN: 
        result = handleSelectBoolean(cr); 
        break;
    case SELECT_SINGLE:
        result = handleSelectSynonym(cr, selectionByQuery);
        break;
    case SELECT_TUPLE:
        result = handleSelectTuple(cr, selectionByQuery);
        break;
    default:
        break;
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

list<string> ResultFormatter::handleSelectBoolean(ClauseResult cr)
{
    list<string> result;
    if (!cr.hasResults()) //If merging has finished and ClauseResult has no results, then BOOLEAN is false
    {
        result.push_back("false");
    }
    else
    {
        result.push_back("true"); //If ClauseResult has results, Select BOOLEAN is true
    }
    return result;
}

list<string> ResultFormatter::handleSelectSynonym(ClauseResult cr, SelectClause selectedClause)
{
    list<string> result;
    if (cr.hasResults())
    {
        Entity argType = selectedClause.getSingleArgType();
        string synonymToGetResultFor = selectedClause.getSingleArg();

        //If result is of type int, get direct results from ClauseResult
        if (argType == STMT || argType == ASSIGN || argType == WHILE || argType == IF || argType == PROG_LINE || argType == CONSTANT || argType == STMTLIST)
        {
            result = convertListOfIntsToListOfStrings(cr.getSynonymResults(synonymToGetResultFor));
        }

        //If result is of type string, convert mapping of ints to strings from PKB 
        else if (argType == PROCEDURE || argType == VARIABLE || argType == CALL)
        {
            result = pkbInstance->convertIdxToString(cr.getSynonymResults(synonymToGetResultFor), argType);
        }

    }

    return result;
}

list<string> ResultFormatter::handleSelectTuple(ClauseResult cr, SelectClause selectedClause)
{
    list<string> result;
    return result;
}

list<string> ResultFormatter::handleNoResult(QueryTree qt)
{
    SelectClause selectionByQuery = qt.getSelectClause();
    list<string> result;
    if (selectionByQuery.getSelectionType() == SELECT_BOOLEAN)
    {
        result.push_back("false");
    }
    return result;
}



