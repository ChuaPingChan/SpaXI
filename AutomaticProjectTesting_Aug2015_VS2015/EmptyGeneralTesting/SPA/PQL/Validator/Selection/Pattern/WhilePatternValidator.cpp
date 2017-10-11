#include "WhilePatternValidator.h"

WhilePatternValidator::WhilePatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree * qtPtrNew)
    :PatternValidator(patternType, patternSyn, paramStr, qtPtrNew)
{
}

WhilePatternValidator::~WhilePatternValidator()
{
}

void WhilePatternValidator::validate()
{
    string firstArg = extractArgOne(paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->validity = true;
    }
    else {
        this->validity = false;
    }
}

bool WhilePatternValidator::isValid()
{
    return this->validity;
}

bool WhilePatternValidator::isValidArgOne(string argOne)
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

bool WhilePatternValidator::isValidArgTwo(string argTwo)
{
    if (argTwo == "_")
    {
        this->argTwoType = UNDERSCORE;
        return true;
    }

    else
    {
        return false;
    }
}

string WhilePatternValidator::extractArgOne(string str)
{
    string delimFirst = "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

string WhilePatternValidator::extractArgTwo(string str)
{
    string delimFirst = ",";
    string delimSecond = ")";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}
