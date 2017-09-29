#include "ModifiesValidator.h"

ModifiesValidator::ModifiesValidator(string rel, string str)
{
    this->rel = rel;
    this->paramStr = str;
}

ModifiesValidator::~ModifiesValidator()
{
}

void ModifiesValidator::validate()
{
    string firstArg = getArgOne(rel, paramStr);
    string secondArg = getArgTwo(paramStr);

    if (firstArg == secondArg) {
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
        this->argOneType = "";
        this->argTwoType = "";
        this->validity = false;
    }
}

bool ModifiesValidator::isValidArgOne(string argOne)
{
    QueryTree qt = *(this->qtPtr);

    if (isArgumentInClause(argOne, qt.getAssigns()))
    {
        this->argOneType = "assign";
        return true;
    } 
    
    else if (isArgumentInClause(argOne, qt.getStmts()))
    {
        this->argOneType = "stmt";
        return true;
    }

    else if (isArgumentInClause(argOne, qt.getWhiles()))
    {
        this->argOneType = "while";
        return true;
    }

    else if (isIntegerRegexCheck(argOne))
    {
        this->argOneType = "int";
        return true;
    }

    else 
    {
        return false;
    }
}

bool ModifiesValidator::isValidArgTwo(string argTwo)
{
    QueryTree qt = *(this->qtPtr);

    if (isArgumentInClause(argTwo, qt.getVars())) { //if arg2 is a variable synonym
        this->argTwoType = "var";
        return true;
    }

    else if (argTwo == "_") {
        this->argTwoType = argTwo;
        return true;
    }

    else if (isIdentWithInvertedCommas(argTwo))
    {
        this->argTwoType = "ident";
        return true;
    }

    else
    {
        return false;
    }
}

bool ModifiesValidator::isValid()
{
    return this->validity;
}
