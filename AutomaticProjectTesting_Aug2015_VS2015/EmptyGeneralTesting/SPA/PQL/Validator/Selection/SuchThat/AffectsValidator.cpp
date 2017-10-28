#include "AffectsValidator.h"

AffectsValidator::AffectsValidator(Relationship rel, string paramStr, QueryTree * qtPtrNew)
    :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

AffectsValidator::~AffectsValidator()
{
}

void AffectsValidator::validate()
{
    string firstArg = extractArgOne(rel, paramStr);
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

bool AffectsValidator::isValid()
{
    return this->validity;
}

bool AffectsValidator::isValidArgOne(string argOne)
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

    else if (qtPtr->isEntitySynonymExist(argOne, PROG_LINE))
    {
        this->argOneType = PROG_LINE;
        return true;
    }

    else if (RegexValidators::isValidIntegerRegex(argOne))
    {
        this->argOneType = INTEGER;
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

bool AffectsValidator::isValidArgTwo(string argTwo)
{
    if (qtPtr->isEntitySynonymExist(argTwo, STMT))
    {
        this->argTwoType = STMT;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argTwo, ASSIGN))
    {
        this->argTwoType = ASSIGN;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argTwo, PROG_LINE))
    {
        this->argTwoType = PROG_LINE;
        return true;
    }

    else if (RegexValidators::isValidIntegerRegex(argTwo))
    {
        this->argTwoType = INTEGER;
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
