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
    string processedStr = Formatter::removeAllSpaces(str);
    string patternSyn = extractPatternSynonym(processedStr);
    int patternType = getPatternType(patternSyn);

    PatternValidator *patternValidator;

    if (patternType == ASSSIGN_PATTERN) {
        patternValidator = new AssignPatternValidator(patternType, patternSyn, processedStr, qtPtr);
    }
    else if (patternType == WHILE_PATTERN) {
        //patternValidator = new WhilePatternValidator(patternType, patternSyn, processedStr, qtPtr);
    }
    else if (patternType == If_PATTERN) {
        //patternValidator = new IfPatternValidator(patternType, patternSyn, processedStr, qtPtr);
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

int PatternHandler::getPatternType(string patternSyn)
{
    if (qtPtr->isENTITYSynonymExist(patternSyn, ASSIGN))
    {
        return ASSSIGN_PATTERN;
    }
    else if (qtPtr->isENTITYSynonymExist(patternSyn, WHILE))
    {
        return WHILE_PATTERN;
    }
    else if (qtPtr->isENTITYSynonymExist(patternSyn, IF))
    {
        return If_PATTERN;
    }
    else {
        return -1;  //TODO: Throw exception
    }
}

string PatternHandler::extractPatternSynonym(string str)
{
    string delimFirst = PatternValidator::PATTERN_KEYWORD;
    string delimSecond = "(";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

PatternClause PatternHandler::makePatternClause(PatternValidator pv)
{
    int patternType = pv.getPatternType();
    int argOneType = pv.getArgOneType();
    int argTwoType = pv.getArgTwoType();
    int argThreeType = pv.getArgThreeType();
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
