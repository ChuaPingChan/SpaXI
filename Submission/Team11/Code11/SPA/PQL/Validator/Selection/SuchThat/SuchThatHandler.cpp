#include "SuchThatHandler.h"
#include <stdexcept>

SuchThatHandler::SuchThatHandler(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


SuchThatHandler::~SuchThatHandler()
{
}

/*
* Pre-cond: str pass RELREF_REGEX
* Post-Cond: If true, SuchThat clause stored in QueryTree
* Returns true when suchthat is semantically valid
*/
bool SuchThatHandler::isValidSuchThat(string str)
{
    string processedStr = Formatter::removeAllSpacesAndTabs(str);
    string relStr = getSuchThatKeyWord(processedStr);
    
    int rel;
    try {
        rel = getRelIndex(relStr);
    }
    catch (RelationshipNotFoundException& rnfe) {
        return false;
    }

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
        case CALLS:
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
            break;
        default: 
            return false;
    }

    suchThatValidator->validate();

    if (suchThatValidator->isValid()) {
        SuchThatClause suchThatClause = makeSuchThatClause(*suchThatValidator);
        storeInQueryTree(suchThatClause);
        delete suchThatValidator;
        suchThatValidator = NULL;
        return true;
    }
    else
    {
        return false;
    }
}

string SuchThatHandler::getSuchThatKeyWord(string str)
{
    regex suchThatKeywordRegex(RegexValidators::RELATIONSHIP_KEYWORD_REGEX);
    smatch foundMatch;

    regex_search(str, foundMatch, suchThatKeywordRegex);
    return foundMatch[1];
}

/*
* Returns the enum form of relationship
* Throws RelationshipNotFoundException when suchthat relationship cannot be determined
*/
Relationship SuchThatHandler::getRelIndex(string rel)
{
    try {
        return MAP_STR_TO_REL.at(rel);
    } catch (out_of_range& oore) {
        throw RelationshipNotFoundException("In SuchThatHandler.getRelIndex(rel). Relationship do not match valid Relationship. Relationship cannot be assigned. Input String: " + rel);
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
