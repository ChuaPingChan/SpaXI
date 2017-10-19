#include "PatternHandler.h"


PatternHandler::PatternHandler(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

PatternHandler::~PatternHandler()
{
}

bool PatternHandler::isValidPattern(string str)
{
    string processedStr = Formatter::removeAllSpacesAndTabs(str);
    string patternSyn = extractPatternSynonym(processedStr);
    PatternType patternType = getPatternType(patternSyn);

    PatternValidator *patternValidator;

    if (patternType == ASSIGN_PATTERN) {
        patternValidator = new AssignPatternValidator(patternType, patternSyn, processedStr, qtPtr);
    }
    else if (patternType == WHILE_PATTERN) {
        patternValidator = new WhilePatternValidator(patternType, patternSyn, processedStr, qtPtr);
    }
    else if (patternType == IF_PATTERN) {
        patternValidator = new IfPatternValidator(patternType, patternSyn, processedStr, qtPtr);
    }
    else {
        return false;
    }

    patternValidator->validate();

    if (patternValidator->isValid()) {
        PatternClause patternClause = makePatternClause(*patternValidator);
        storeInQueryTree(patternClause);
        return true;
    }
    else {
        return false;
    }
}

PatternType PatternHandler::getPatternType(string patternSyn)
{
    if (qtPtr->isEntitySynonymExist(patternSyn, ASSIGN))
    {
        return ASSIGN_PATTERN;
    }
    else if (qtPtr->isEntitySynonymExist(patternSyn, WHILE))
    {
        return WHILE_PATTERN;
    }
    else if (qtPtr->isEntitySynonymExist(patternSyn, IF))
    {
        return IF_PATTERN;
    }
    //else 
    //{
    //    return -1;  //TODO: Throw exception
    //}
}

string PatternHandler::extractPatternSynonym(string str)
{
    string delimFirst = "";
    string delimSecond = "(";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

PatternClause PatternHandler::makePatternClause(PatternValidator pv)
{
    PatternType patternType = pv.getPatternType();
    Entity argOneType = pv.getArgOneType();
    Entity argTwoType = pv.getArgTwoType();
    Entity argThreeType = pv.getArgThreeType();
    string patternSyn = pv.getPatternSynonym();
    string argOne = pv.getArgOne();
    string argTwo = pv.getArgTwo();
    string argThree = pv.getArgThree();

    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

bool PatternHandler::storeInQueryTree(PatternClause pc)
{
    qtPtr->insertPattern(pc);
    return true;
}
