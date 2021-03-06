#include "ResultFormatter.h"


using namespace std;

/*This class checks the selection type of the select clause has 
(whether it is Select BOOLEAN, Select singleSynonym or Select Tuple)
and formats the results to be displayed to the UI.*/

const string ResultFormatter::TRUE = "true";
const string ResultFormatter::FALSE = "false";

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
        result.push_back(FALSE);
    }
    return result;
}

/******************
* Helper methods *
******************/



/* Formats result when Select type is BOOLEAN */
list<string> ResultFormatter::handleSelectBoolean(ClauseResult cr)
{
    list<string> result;
    if (!cr.hasResults()) //If merging has finished and ClauseResult has no results, then BOOLEAN is false
    {
        result.push_back(FALSE);
    }
    else
    {
        result.push_back(TRUE); //If ClauseResult has results, Select BOOLEAN is true
    }
    return result;
}

/* Formats result when Select type is a single synonym */
list<string> ResultFormatter::handleSelectSynonym(ClauseResult cr, SelectClause selectedClause)
{
    list<string> result;
    if (cr.hasResults())
    {
        Entity argType = selectedClause.getSingleArgType();
        string synonymToGetResultFor = selectedClause.getSingleArg();

        if (argType == PROCEDURE || argType == VARIABLE || selectedClause.isAttributeProcName == true)
        {            
            result = pkbInstance->convertIdxToString(cr.getSynonymResults(synonymToGetResultFor), argType);
        }

        //If result is of type int, get direct results from ClauseResult
        else if (argType == STMT || argType == ASSIGN || argType == WHILE || argType == IF || argType == PROG_LINE || argType == CALL || argType == CONSTANT || argType == STMTLIST)
        {
            result = convertListOfIntsToListOfStrings(cr.getSynonymResults(synonymToGetResultFor));
        }

    }

    return result;
}

/* Formats result when Select type is a tuple */
list<string> ResultFormatter::handleSelectTuple(ClauseResult cr, SelectClause selectedClause)
{
    list<string> result;
    vector<string> synonymsFromSelectedClause = selectedClause.getTupleArgs();
    list<string> synonyms;
    synonyms.assign(synonymsFromSelectedClause.begin(), synonymsFromSelectedClause.end()); //Convert from vector to list to call ClauseResult API

    list<list<int>> resultListOfTuple = cr.getSynonymResults(synonyms); //Get all results for the Selected Synonyms in TUPLE
    for (auto it : resultListOfTuple) //iterate over each row of tuple result
    {
        list<int> curList = it; //current row of tuple result
        list<string> tempListOfStrings;
        int index = 0;
        for (int curElement : curList) //iterate over each column of tuple result
        {
            Entity argType = selectedClause.getTupleArgTypeAt(index); //get Entity type at current index
            vector<bool> flagsForCall = selectedClause.isAttributeProcNameForTuple; //get true/false flags for Call.procName to get mapping from PKB

            if (argType == VARIABLE || argType == PROCEDURE || (argType == CALL && flagsForCall.at(index)))
            {
                tempListOfStrings.push_back(pkbInstance->convertIdxToString(curElement, argType)); //get mapping of int to string
            }
            else
            {
                tempListOfStrings.push_back(to_string(curElement)); //convert int to string
            }
            index++;
        }

        result.push_back(convertListOfStringsToSingleString(tempListOfStrings)); //convert list of strings to one string
    }
    
    return result;
}

/* Convert a list of integers to a list of strings */
list<string> ResultFormatter::convertListOfIntsToListOfStrings(list<int> listOfInts)
{
    list<string> convertedFromInt;
    for (int i : listOfInts)
    {
        convertedFromInt.push_back(to_string(i));
    }

    return convertedFromInt;
}

/* Add whitespaces between elements and comma at the end of the list */
string ResultFormatter::convertListOfStringsToSingleString(list<string> singleSynResult)
{
    string result;
    for (string s : singleSynResult)
    {
        result.append(s);
        result.append(" ");
    }
    result.erase(result.size() - 1, result.size());
    return result;
}






