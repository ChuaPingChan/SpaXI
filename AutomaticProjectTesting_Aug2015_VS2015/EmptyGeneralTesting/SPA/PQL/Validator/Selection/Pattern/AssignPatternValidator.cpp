#include "AssignPatternValidator.h"

AssignPatternValidator::AssignPatternValidator(int patternType, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, paramStr, qtPtrNew)
{
}


AssignPatternValidator::~AssignPatternValidator()
{
}

void AssignPatternValidator::validate()
{
    string firstArg = extractArgOne(paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->validity = true;
    }
    else {
        this->argOne = "";
        this->argTwo = "";
        this->argOneType = UNKNOWN;
        this->argTwoType = UNKNOWN;
        this->validity = false;
    }
}

bool AssignPatternValidator::isValid()
{
    return this->validity;
}

bool AssignPatternValidator::isValidArgOne(string argOne)
{
    QueryTree qt = *(this->qtPtr);
    if (qt.isEntitySynonymExist(argOne, VARIABLE))
    {
        this->argOneType = VARIABLE;
        return true;
    }

    else if (argOne == "_")
    {
        this->argOneType = UNDERSCORE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argOne))
    {
        this->argOneType = IDENT_WITHQUOTES;
        return true;
    }

    else
    {
        return false;
    }
    
}

bool AssignPatternValidator::isValidArgTwo(string argTwo)
{
    if (argTwo == "_")
    {
        this->argTwoType = UNDERSCORE;
        return true;
    }
    
    else if (RegexValidators::isValidExpressionSpec(argTwo))
    {
        this->argTwoType = EXPRESSION_SPEC;
        return true;
    }

    else
    {
        return false;
    }
}

string AssignPatternValidator::extractArgOne(string str)
{
    string delimFirst = "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}

string AssignPatternValidator::extractArgTwo(string str)
{
    string delimFirst = "(";
    string delimSecond = ")";

    return Formatter::getBetweenTwoStrings(str, delimFirst, delimSecond);
}
