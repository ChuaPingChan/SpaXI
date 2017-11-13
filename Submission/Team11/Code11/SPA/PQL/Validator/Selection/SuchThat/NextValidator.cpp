#include "NextValidator.h"

NextValidator::NextValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew)
    :SuchThatValidator(rel, paramStr, qtPtrNew)
{
}

NextValidator::~NextValidator()
{
}

void NextValidator::validate()
{
    string firstArg = extractArgOne(rel, paramStr);
    string secondArg = extractArgTwo(paramStr);

    if (this->rel == NEXT && firstArg == secondArg && firstArg != UNDERSCORE_STRING) {    //Because can never be 2 underlines or 2 int or 2 same synonym or 2 same synonymType
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

bool NextValidator::isValid()
{
    return this->validity;
}

bool NextValidator::isValidArgOne(string argOne)
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

    else if (qtPtr->isEntitySynonymExist(argOne, IF))
    {
        this->argOneType = IF;
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

bool NextValidator::isValidArgTwo(string argTwo)
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

    else if (qtPtr->isEntitySynonymExist(argTwo, IF))
    {
        this->argTwoType = IF;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argTwo, PROG_LINE))
    {
        this->argTwoType = PROG_LINE;
        return true;
    }

    else if (qtPtr->isEntitySynonymExist(argTwo, CALL))
    {
        this->argTwoType = CALL;
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
