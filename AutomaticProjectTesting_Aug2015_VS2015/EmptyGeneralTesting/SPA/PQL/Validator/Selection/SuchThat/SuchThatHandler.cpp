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
    string relStr = getSuchThatKeyWord(processedStr);
    int rel = getRelIndex(relStr);

    SuchThatValidator *suchThatValidator;

    if (rel == MODIFIES) {
        suchThatValidator = new ModifiesValidator(MODIFIES, processedStr, qtPtr);
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

int SuchThatHandler::getRelIndex(string rel)
{
    if (rel == RELATIONSHIP_STRING[MODIFIES]) {
        return MODIFIES;
    }
    else if (rel == RELATIONSHIP_STRING[USES]) {
        return USES;
    }
    else if (rel == RELATIONSHIP_STRING[PARENT]) {
        return PARENT;
    }
    else if (rel == RELATIONSHIP_STRING[PARENTSTAR]) {
        return PARENTSTAR;
    }
    else if (rel == RELATIONSHIP_STRING[FOLLOWS]) {
        return FOLLOWS;
    }
    else if (rel == RELATIONSHIP_STRING[FOLLOWSSTAR]) {
        return FOLLOWS;
    }
    else if (rel == RELATIONSHIP_STRING[CALLS]) {
        return CALLS;
    }
    else if (rel == RELATIONSHIP_STRING[CALLSSTAR]) {
        return CALLSSTAR;
    }
    else if (rel == RELATIONSHIP_STRING[NEXT]) {
        return NEXT;
    }
    else if (rel == RELATIONSHIP_STRING[NEXTSTAR]) {
        return NEXTSTAR;
    }
    else if (rel == RELATIONSHIP_STRING[AFFECTS]) {
        return AFFECTS;
    }
    else if (rel == RELATIONSHIP_STRING[AFFECTSSTAR]) {
        return AFFECTSSTAR;
    }
    else {
        return -1;  //TODO: Throw exception to say inalid
    }
}

SuchThatClause SuchThatHandler::makeSuchThatClause(SuchThatValidator stv)
{
    int rel = stv.getRel();
    int argOneType = stv.getArgOneType();
    int argTwoType = stv.getArgTwoType();
    string argOne = stv.getArgOne();
    string argTwo = stv.getArgTwo();

    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

bool SuchThatHandler::storeInQueryTree(SuchThatClause stc)
{
    qtPtr->insertSuchThat(stc);
    return true;
}



