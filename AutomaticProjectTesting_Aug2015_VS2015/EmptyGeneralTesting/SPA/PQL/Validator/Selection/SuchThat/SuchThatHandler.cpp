#include "SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


SuchThatHandler::~SuchThatHandler()
{
}

bool SuchThatHandler::isValidSuchThat(string str)
{
    string processedStr = Formatter::removeAllSpaces(str);
    string rel = getSuchThatKeyWord(processedStr);

    SuchThatValidator suchThatValidator(qtPtr);

    if (rel == "Modifies") {
        suchThatValidator = ModifiesValidator(rel, processedStr);
    }

    if (suchThatValidator.isValid()) {
        SuchThatClause suchThatClause = makeSuchThatClause(suchThatValidator);
        storeInQueryTree(suchThatClause);
        return true;
    }
    else
    {
        return false;
    }
}

//TODO: Put inside regex table (Only the regex part)
string SuchThatHandler::getSuchThatKeyWord(string str)
{
    string SUCH_THAT_KEYWORD = "(Modifies|Uses|Parent|Parent*|Follows|Follows*|Calls|Calls*|Next|Next*|Affects|Affects)";
    regex suchThatKeywordRegex(SUCH_THAT_KEYWORD);
    smatch foundMatch;
    regex_search(str, foundMatch, suchThatKeywordRegex);
    string suchThatKeyword = foundMatch[1];

    return suchThatKeyword;
}

//TODO: Change the index number
int SuchThatHandler::getRelIndex(string rel)
{
    if (rel == "Modifies") {
        return 0;
    }
    return 0;   //stub
}

//TODO: Change the index reference
int SuchThatHandler::getArgTypeIndex(string arg)
{
    if (arg == "stmt") {
        return 0;
    }
    return 0;   //stub
}

SuchThatClause SuchThatHandler::makeSuchThatClause(SuchThatValidator stv)
{
    int rel = getRelIndex(stv.getRel());
    int argOneType = getArgTypeIndex(stv.getArgOneType());
    int argTwoType = getArgTypeIndex(stv.getArgTwoType());
    string argOne = stv.getArgOne();
    string argTwo = stv.getArgTwo();

    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

bool SuchThatHandler::storeInQueryTree(SuchThatClause stc)
{
    qtPtr->insertSuchThat(stc);
    return true;
}



