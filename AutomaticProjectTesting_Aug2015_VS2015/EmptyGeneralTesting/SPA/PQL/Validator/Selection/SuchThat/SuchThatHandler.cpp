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

    SuchThatValidator *suchThatValidator;

    if (rel == SuchThatValidator::MODIFIES) {
        suchThatValidator = new ModifiesValidator(rel, processedStr, qtPtr);
    }

    suchThatValidator->validate();

    if (suchThatValidator->isValid()) {
        SuchThatClause suchThatClause = makeSuchThatClause(*suchThatValidator);
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
    if (rel == SuchThatValidator::MODIFIES) {
        return 0;
    }
    else if (rel == SuchThatValidator::USES) {
        return 1;
    }
    else if (rel == SuchThatValidator::PARENT) {
        return 2;
    }
    else if (rel == SuchThatValidator::PARENTSTAR) {
        return 3;
    }
    else if (rel == SuchThatValidator::FOLLOWS) {
        return 4;
    }
    else if (rel == SuchThatValidator::FOLLOWSSTAR) {
        return 5;
    }
    else if (rel == SuchThatValidator::CALLS) {
        return 6;
    }
    else if (rel == SuchThatValidator::CALLSSTAR) {
        return 7;
    }
    else if (rel == SuchThatValidator::NEXT) {
        return 8;
    }
    else if (rel == SuchThatValidator::NEXTSTAR) {
        return 9;
    }
    else if (rel == SuchThatValidator::AFFECTS) {
        return 10;
    }
    else if (rel == SuchThatValidator::AFFECTSSTAR) {
        return 11;
    }
    else {
        return -1;  //TODO: Throw exception to say inalid
    }
}

//TODO: Change the index reference
int SuchThatHandler::getArgTypeIndex(string arg)
{
    if (arg == SuchThatValidator::STMT) {
        return 0;
    }
    else if (arg == SuchThatValidator::ASSIGN) {
        return 1;
    }
    else if (arg == SuchThatValidator::WHILE) {
        return 2;
    }
    else if (arg == SuchThatValidator::IF) {
        return 3;
    }
    else if (arg == SuchThatValidator::PROG_LINE) {
        return 4;
    }
    else if (arg == SuchThatValidator::CALL) {
        return 5;
    }
    else if (arg == SuchThatValidator::PROCEDURE) {
        return 6;
    }
    else if (arg == SuchThatValidator::VARIABLE) {
        return 7;
    }
    else if (arg == SuchThatValidator::INTEGER) {
        return 8;
    }
    else {
        return -1;  //TODO: Throw excception to say invalid
    }
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



