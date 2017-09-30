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
        this->argTwoType = "variable";
        return true;
    }

    else if (argTwo == "_") {
        this->argTwoType = "underscore";
        return true;
    }

    else if (isIdentWithQuotes(argTwo))
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
