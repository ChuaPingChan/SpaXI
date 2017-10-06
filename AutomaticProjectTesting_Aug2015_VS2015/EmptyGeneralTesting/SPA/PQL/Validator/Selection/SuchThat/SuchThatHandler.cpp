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

    switch(rel) {
        case MODIFIES:
            suchThatValidator = new ModifiesValidator(MODIFIES, processedStr, qtPtr);
            break;
        case USES:
            suchThatValidator = new UsesValidator(USES, processedStr, qtPtr);
            break;
        case PARENT:
            suchThatValidator = new ParentValidator(PARENT, processedStr, qtPtr);
            break;
        case PARENTSTAR:
            suchThatValidator = new ParentValidator(PARENTSTAR, processedStr, qtPtr);
            break;
        case FOLLOWS:
            suchThatValidator = new FollowsValidator(FOLLOWS, processedStr, qtPtr);
            break;
        case FOLLOWSSTAR:
            suchThatValidator = new FollowsValidator(FOLLOWSSTAR, processedStr, qtPtr);
            break;
        /*case CALLS:
            suchThatValidator = new CallsValidator(CALLS, processedStr, qtPtr);
            break;
        case CALLSSTAR:
            suchThatValidator = new CallsValidator(CALLSSTAR, processedStr, qtPtr);
            break;
        case NEXT:
            suchThatValidator = new NextValidator(NEXT, processedStr, qtPtr);
            break;
        case NEXTSTAR:
            suchThatValidator = new NextValidator(NEXTSTAR, processedStr, qtPtr);
            break;
        case AFFECTS:
            suchThatValidator = new AffectsValidator(AFFECTS, processedStr, qtPtr);
            break;
        case AFFECTSSTAR:
            suchThatValidator = new AffectsValidator(AFFECTSSTAR, processedStr, qtPtr);
            break;*/
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

//TODO: Throw exception if cant find
string SuchThatHandler::getSuchThatKeyWord(string str)
{
    regex suchThatKeywordRegex(RegexValidators::RELATIONSHIP_KEYWORD_REGEX);
    smatch foundMatch;

    regex_search(str, foundMatch, suchThatKeywordRegex);
    return foundMatch[1];
}

int SuchThatHandler::getRelIndex(string rel)
{
    if (rel == RELATIONSHIP_STRING_ARRAY[MODIFIES]) {
        return MODIFIES;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[USES]) {
        return USES;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[PARENT]) {
        return PARENT;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[PARENTSTAR]) {
        return PARENTSTAR;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[FOLLOWS]) {
        return FOLLOWS;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[FOLLOWSSTAR]) {
        return FOLLOWSSTAR;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[CALLS]) {
        return CALLS;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[CALLSSTAR]) {
        return CALLSSTAR;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[NEXT]) {
        return NEXT;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[NEXTSTAR]) {
        return NEXTSTAR;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[AFFECTS]) {
        return AFFECTS;
    }
    else if (rel == RELATIONSHIP_STRING_ARRAY[AFFECTSSTAR]) {
        return AFFECTSSTAR;
    }
    else {
        return -1;  //TODO: Throw exception to say inalid
    }
}

SuchThatClause SuchThatHandler::makeSuchThatClause(SuchThatValidator stv)
{
    Relationship rel = stv.getRel();
    Entity argOneType = stv.getArgOneType();
    Entity argTwoType = stv.getArgTwoType();
    string argOne = stv.getArgOne();
    string argTwo = stv.getArgTwo();

    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

bool SuchThatHandler::storeInQueryTree(SuchThatClause stc)
{
    qtPtr->insertSuchThat(stc);
    return true;
}
