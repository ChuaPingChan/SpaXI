#include "CallsValidator.h"

CallsValidator::CallsValidator(Relationship rel, string paramStr, QueryTree * qtPtrNew) :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

CallsValidator::~CallsValidator()
{
}

void CallsValidator::validate()
{
    string firstArg = extractArgOne(rel, paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (firstArg == secondArg && firstArg!=UNDERSCORE_STRING) {    //Cannot have the same procedure as arguments but can have underscore in both, so need additional check
        this->validity = false;
        return;
    }

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->validity = true;
    }
    else {
        this->validity = false;
    }
}

bool CallsValidator::isValid()
{
    return this->validity;
}

bool CallsValidator::isValidArgOne(string argOne)
{
    if (qtPtr->isEntitySynonymExist(argOne, PROCEDURE))
    {
        this->argOneType = PROCEDURE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argOne))
    {
        argOne = Formatter::removeAllQuotes(argOne);
        this->argOneType = IDENT_WITHOUTQUOTES;
        return true;
    }

    else if (argOne == UNDERSCORE_STRING)
    {
        this->argOneType = UNDERSCORE;
        return true;
    }

    else
    {
        return false;
    }
}

bool CallsValidator::isValidArgTwo(string argTwo)
{
    if (qtPtr->isEntitySynonymExist(argTwo, PROCEDURE))
    {
        this->argTwoType = PROCEDURE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argTwo))
    {
        argTwo = Formatter::removeAllQuotes(argTwo);
        this->argTwoType = IDENT_WITHOUTQUOTES;
        return true;
    }

    else if (argTwo == UNDERSCORE_STRING)
    {
        this->argTwoType = UNDERSCORE;
        return true;
    }

    else
    {
        return false;
    }
}

