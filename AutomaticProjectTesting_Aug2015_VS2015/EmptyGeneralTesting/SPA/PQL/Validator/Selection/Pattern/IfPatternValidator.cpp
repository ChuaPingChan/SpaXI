#include "IfPatternValidator.h"

IfPatternValidator::IfPatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, patternSyn, paramStr, qtPtrNew)
{
}


IfPatternValidator::~IfPatternValidator()
{
}

void IfPatternValidator::validate()
{
    string firstArg = extractArgOne(paramStr);
    string secondArg = extractArgTwo(paramStr);
    string thirdArg = extractArgThree(paramStr);

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg) && isValidArgThree(thirdArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->argThree = thirdArg;
        this->validity = true;
    }
    else {
        this->validity = false;
    }
}

bool IfPatternValidator::isValid()
{
    return this->validity;
}

bool IfPatternValidator::isValidArgOne(string argOne)
{
    if (qtPtr->isEntitySynonymExist(argOne, VARIABLE))
    {
        this->argOneType = VARIABLE;
        return true;
    }

    else if (RegexValidators::isValidUnderscoreRegex(argOne))
    {
        this->argOneType = UNDERSCORE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argOne))
    {
        this->argOneType = IDENT_WITHOUTQUOTES;
        return true;
    }

    else
    {
        return false;
    }
}

bool IfPatternValidator::isValidArgTwo(string argTwo)
{
    if (RegexValidators::isValidUnderscoreRegex(argTwo))
    {
        this->argTwoType = UNDERSCORE;
        return true;
    }

    else
    {
        return false;
    }
}

bool IfPatternValidator::isValidArgThree(string argThree)
{
    if (RegexValidators::isValidUnderscoreRegex(argThree))
    {
        this->argThreeType = UNDERSCORE;
        return true;
    }

    else
    {
        return false;
    }
}

string IfPatternValidator::extractArgOne(string str)
{
    string delimFirst = "(";
    string delimSecond = ",";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

string IfPatternValidator::extractArgTwo(string str)
{
    string delimFirst = ",";
    string delimSecond = ",";

    return Formatter::getBetweenTwoDelims(str, delimFirst, 1, delimSecond, 1);
}

string IfPatternValidator::extractArgThree(string str)
{
    string delimFirst = ",";
    string delimSecond = ")";

    return Formatter::getBetweenTwoDelims(str, delimFirst, 2, delimSecond, 1);
}
