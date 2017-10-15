#include "AssignPatternValidator.h"

AssignPatternValidator::AssignPatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, patternSyn, paramStr, qtPtrNew)
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
        this->validity = false;
    }
}

bool AssignPatternValidator::isValid()
{
    return this->validity;
}

bool AssignPatternValidator::isValidArgOne(string &argOne)
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
        argOne = Formatter::removeAllQuotes(argOne);
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
    
    //TODO: remove quotes, check for well form expression
    else if (RegexValidators::isValidExpressionSpecPartialRegex(argTwo))
    {
        this->argTwoType = EXPRESSION_SPEC_PARTIAL;
        return true;
    }

    //TODO: remove quotes, check for well form expression
    else if (RegexValidators::isValidExpressionSpecExactRegex(argTwo))
    {
        this->argTwoType = EXPRESSION_SPEC_EXACT;
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

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}

string AssignPatternValidator::extractArgTwo(string str)
{
    string delimFirst = ",";
    string delimSecond = ")";

    return Formatter::getBetweenTwoDelims(str, delimFirst, delimSecond);
}
