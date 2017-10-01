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
    string patternType = getPatternKeyword(processedStr);

    PatternValidator *patternValidator;

    if (patternType == PatternValidator::ASSIGN) {
        patternValidator = new AssignPatternValidator(patternType, processedStr, qtPtr);
    }
    else if (patternType == PatternValidator::WHILE) {
        //patternValidator = new WhilePatternValidator(patternType, processedStr, qtPtr);
    }
    else if (patternType == PatternValidator::IF) {
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

string PatternHandler::getPatternKeyword(string str)
{
    string argOne = extractArgOne(str);
    if (isArgumentInClause(argOne, qtPtr->getAssigns())) {
        return PatternValidator::ASSIGN;
    }
    else if (isArgumentInClause(argOne, qtPtr->getWhiles())) {
        return PatternValidator::WHILE;
    }
    /*else if (isArgumentInClause(argOne, qtPtr->getIfs())) {
        return PatternValidator::IF;
    }*/
    else {
        return "";  //TODO: Throw exception
    }
}

string PatternHandler::extractArgOne(string str)
{
    string delimFirst = "pattern";
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

int PatternHandler::getPatternTypeIndex(string patternType)
{
    if (patternType == PatternValidator::ASSIGN) {
        return 1;
    }
    else if (patternType == PatternValidator::WHILE) {
        return 2;
    }
    else if (patternType == PatternValidator::IF) {
        return 3;
    }
    else {
        return -1;  //TODO: Throw exception
    }
}

//TODO: Change the index reference
int PatternHandler::getArgTypeIndex(string arg)
{
    if (arg == PatternValidator::VARIABLE) {
        return 7;
    }
    else if (arg == PatternValidator::UNDERSCORE) {
        return 9;
    }
    else if (arg == PatternValidator::IDENT_WITH_QUOTES) {
        return 10;
    }
    else if (arg == PatternValidator::EXPRESSION_SPEC) {
        return 11;
    }
    else {
        return -1;  //TODO: Throw excception to say invalid
    }
}

PatternClause PatternHandler::makePatternClause(PatternValidator pv)
{
    int patternTypeIdx = getPatternTypeIndex(pv.getPatternType());
    int argOneType = getArgTypeIndex(pv.getArgOneType());
    int argTwoType = getArgTypeIndex(pv.getArgTwoType());
    int argThreeType = getArgTypeIndex(pv.getArgThreeType());
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
