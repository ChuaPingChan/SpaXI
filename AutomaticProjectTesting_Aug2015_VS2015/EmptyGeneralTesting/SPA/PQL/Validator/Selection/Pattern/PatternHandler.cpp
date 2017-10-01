#include "PatternHandler.h"

const string PatternHandler::PATTERN_KEYWORD = "pattern";

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
    int patternType = getPatternType(processedStr);

    PatternValidator *patternValidator;

    if (patternType == ASSSIGN_PATTERN) {
        patternValidator = new AssignPatternValidator(patternType, processedStr, qtPtr);
    }
    else if (patternType == WHILE_PATTERN) {
        //patternValidator = new WhilePatternValidator(patternType, processedStr, qtPtr);
    }
    else if (patternType == If_PATTERN) {
        //patternValidator = new IfPatternValidator(patternType, processedStr, qtPtr);
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

int PatternHandler::getPatternType(string str)
{
    string argOne = extractArgOne(str);
    if (isArgumentInClause(argOne, qtPtr->getAssigns())) {
        return ASSSIGN_PATTERN;
    }
    else if (isArgumentInClause(argOne, qtPtr->getWhiles())) {
        return WHILE_PATTERN;
    }
    /*else if (isArgumentInClause(argOne, qtPtr->getIfs())) {
        return IF_PATTERN;
    }*/
    else {
        return -1;  //TODO: Throw exception
    }
}

string PatternHandler::extractArgOne(string str)
{
    string delimFirst = PATTERN_KEYWORD;
    string delimSecond = "(";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

bool PatternHandler::isArgumentInClause(string arg, unordered_set<string> clause)
{
    if (find(clause.begin(), clause.end(), arg) != clause.end())
        return true;
    else
        return false;
}

PatternClause PatternHandler::makePatternClause(PatternValidator pv)
{
    int patternTypeIdx = pv.getPatternType();
    int argOneType = pv.getArgOneType();
    int argTwoType = pv.getArgTwoType();
    int argThreeType = pv.getArgThreeType();
    string argOne = pv.getArgOne();
    string argTwo = pv.getArgTwo();
    string argThree = pv.getArgThree();

    return PatternClause(patternTypeIdx, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

bool PatternHandler::storeInQueryTree(PatternClause pc)
{
    qtPtr->insertPattern(pc);
    return true;
}
