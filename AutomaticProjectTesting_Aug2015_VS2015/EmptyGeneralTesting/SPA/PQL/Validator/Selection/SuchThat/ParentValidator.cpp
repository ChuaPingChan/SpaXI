#include "ParentValidator.h"

ParentValidator::ParentValidator(Relationship rel, string paramStr, QueryTree * qtPtrNew)
    :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

ParentValidator::~ParentValidator()
{
}

void ParentValidator::validate()
{
    string firstArg = extractArgOne(rel, paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (firstArg == secondArg && firstArg != UNDERSCORE_STRING) {    //Because can never be 2 underlines or 2 int or 2 same synonym or 2 same synonymType
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

bool ParentValidator::isValid()
{
    return this->validity;
}

bool ParentValidator::isValidArgOne(string argOne)
{
    if (qtPtr->isEntitySynonymExist(argOne, STMT))
    {
        this->argOneType = STMT;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argOne, WHILE))
    {
        this->argOneType = WHILE;
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

bool ParentValidator::isValidArgTwo(string argTwo)
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

    else if (qtPtr->isEntitySynonymExist(argTwo, WHILE))
    {
        this->argTwoType = WHILE;
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
