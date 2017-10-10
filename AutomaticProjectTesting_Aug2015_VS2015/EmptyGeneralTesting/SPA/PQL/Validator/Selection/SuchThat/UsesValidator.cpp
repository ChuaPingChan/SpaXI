#include "UsesValidator.h"

UsesValidator::UsesValidator(Relationship rel, string paramStr, QueryTree * qtPtrNew)
    :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

UsesValidator::~UsesValidator()
{
}

void UsesValidator::validate()
{
    string firstArg = extractArgOne(rel, paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (firstArg == secondArg) {    //Because can never be 2 underlines or 2 int or 2 same synonym or 2 same synonymType
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

bool UsesValidator::isValid()
{
    return this->validity;
}

bool UsesValidator::isValidArgOne(string argOne)
{
    if (qtPtr->isEntitySynonymExist(argOne, STMT))
    {
        this->argOneType = STMT;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, ASSIGN))
    {
        this->argOneType = ASSIGN;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, WHILE))
    {
        this->argOneType = WHILE;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, PROG_LINE))
    {
        this->argOneType = PROG_LINE;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, CALL))
    {
        this->argOneType = CALL;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, PROCEDURE))
    {
        this->argOneType = PROCEDURE;
        return true;
    }

    else if (RegexValidators::isValidIntegerRegex(argOne))
    {
        this->argOneType = INTEGER;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argOne))
    {
        argOne = Formatter::removeAllQuotes(argOne);
        this->argOneType = IDENT_WITHOUTQUOTES;
        return true;
    }

    else
    {
        return false;
    }
}

bool UsesValidator::isValidArgTwo(string argTwo)
{
    if (qtPtr->isEntitySynonymExist(argTwo, VARIABLE))
    {
        this->argTwoType = VARIABLE;
        return true;
    }

    else if (argTwo == UNDERSCORE_STRING) {
        this->argTwoType = UNDERSCORE;
        return true;
    }

    else if (RegexValidators::isValidIdentWithQuotesRegex(argTwo))
    {
        argTwo = Formatter::removeAllQuotes(argTwo);
        this->argTwoType = IDENT_WITHOUTQUOTES;
        return true;
    }

    else
    {
        return false;
    }
}

