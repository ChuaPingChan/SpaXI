#include "ResultFormatter.h"


using namespace std;

/*This class checks the selection type of the select clause has 
(whether it is Select BOOLEAN, Select singleSynonym or Select Tuple)
and formats the results to be displayed to the UI.*/
ResultFormatter::ResultFormatter()
{
    this->pkbInstance = PKBMain::getInstance();
}

//This method handles result formatter if the ClauseResult has result
list<string> ResultFormatter::finalResultFromSelection(ClauseResult cr, QueryTree qt)
{
	SelectClause selectionByQuery = qt.getSelectClause();
	list<string> selectSynonym;
	list<string> result;

    SelectionType selectedType = selectionByQuery.getSelectionType(); //Get Selection Type from the SelectClause
    
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

//This method handles result if evaluator has no result/query is invalid and Select type is BOOLEAN.
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
    list<string> synonyms;
    synonyms.assign(selectedClause.getTupleArgs().begin(), selectedClause.getTupleArgs().end());
    list<list<int>> l = cr.getSynonymResults(synonyms);
    vector<list<int>> synonymResults{ std::make_move_iterator(std::begin(l)),std::make_move_iterator(std::end(l)) };
    int size = selectedClause.getTupleArgs().size();

    for (int i = 0; i < size; i++)
    {
        Entity argType = selectedClause.getTupleArgTypeAt(i);
        string synonymToGetResultFor = selectedClause.getTupleArgAt(i);
        list<int> resultForCurrentSynonym = synonymResults.at(i);
        //If result is of type int, get direct results from ClauseResult
        if (argType == STMT || argType == ASSIGN || argType == WHILE || argType == IF || argType == PROG_LINE || argType == CONSTANT || argType == STMTLIST)
        {
            list<string> tempResult = convertListOfIntsToListOfStrings(resultForCurrentSynonym);
            result.push_back(convertListOfStringsToSingleString(tempResult));
        }

        //If result is of type string, convert mapping of ints to strings from PKB 
        else if (argType == PROCEDURE || argType == VARIABLE || argType == CALL)
        {
            list<string> tempResult = pkbInstance->convertIdxToString(resultForCurrentSynonym, argType);
            result.push_back(convertListOfStringsToSingleString(tempResult));
        }
    }

    result = formatForFinalDisplayInTuple(result);
    return result;
}

//Add whitespaces between elements and comma at the end of the list
string ResultFormatter::convertListOfStringsToSingleString(list<string> singleSynResult)
{
    string result;
    for (string s : singleSynResult)
    {
        result.append(" ");
        result.append(s);
    }
    result.append(",");
    return result;
}

//Remove whitespace from first list and comma from the end of the last list
list<string> ResultFormatter::formatForFinalDisplayInTuple(list<string> unformattedResult)
{
    list<string> result;
    string first = unformattedResult.front();
    string last = unformattedResult.back();
    first.erase(0, 1);
    result.push_back(first);
    last.erase(last.size() - 1, last.size());
    
    unformattedResult.pop_back();
    unformattedResult.pop_front();

    for (string s : unformattedResult)
    {
        result.push_back(s);
    }
    result.push_back(last);

    return result;
}





