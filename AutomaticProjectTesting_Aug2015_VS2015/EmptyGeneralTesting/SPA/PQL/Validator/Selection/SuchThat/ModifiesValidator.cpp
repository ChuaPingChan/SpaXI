#include "ModifiesValidator.h"

ModifiesValidator::ModifiesValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew)
    :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

ModifiesValidator::~ModifiesValidator()
{
}

void ModifiesValidator::validate()
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

bool ModifiesValidator::isValid()
{
    return this->validity;
}

bool ModifiesValidator::isValidArgOne(string argOne)
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
        this->argOneType = IDENT_WITHQUOTES;
        return true;
    }

    else 
    {
        return false;
    }
}

bool ModifiesValidator::isValidArgTwo(string argTwo)
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
        this->argTwoType = IDENT_WITHQUOTES;
        return true;
    }

    else
    {
        return false;
    }
}
