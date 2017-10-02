#include "ModifiesValidator.h"

ModifiesValidator::ModifiesValidator(int rel, string paramStr, QueryTree *qtPtrNew)
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
    }

    if (isValidArgOne(firstArg) && isValidArgTwo(secondArg)) {
        this->argOne = firstArg;
        this->argTwo = secondArg;
        this->validity = true;
    }
    else {
        this->argOne = "";
        this->argTwo = "";
        this->argOneType = UNKNWON;
        this->argTwoType = UNKNWON;
        this->validity = false;
    }
}

bool ModifiesValidator::isValid()
{
    return this->validity;
}

bool ModifiesValidator::isValidArgOne(string argOne)
{
    if (qtPtr->isENTITYSynonymExist(argOne, STMT))
    {
        this->argOneType = STMT;
        return true;
    }

    else if (qtPtr->isENTITYSynonymExist(argOne, ASSIGN))
    {
        this->argOneType = ASSIGN;
        return true;
    }

    else if (qtPtr->isENTITYSynonymExist(argOne, WHILE))
    {
        this->argOneType = WHILE;
        return true;
    }

    else if (RegexValidators::isValidIntegerRegex(argOne))
    {
        this->argOneType = INTEGER;
        return true;
    }

    else 
    {
        return false;
    }
}

bool ModifiesValidator::isValidArgTwo(string argTwo)
{
    if (qtPtr->isENTITYSynonymExist(argTwo, VARIABLE))
    {
        this->argTwoType = VARIABLE;
        return true;
    }

    else if (argTwo == "_") {
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
