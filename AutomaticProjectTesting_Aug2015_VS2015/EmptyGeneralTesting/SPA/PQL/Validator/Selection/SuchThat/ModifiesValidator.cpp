#include "ModifiesValidator.h"

ModifiesValidator::ModifiesValidator(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}

ModifiesValidator::~ModifiesValidator()
{
}


void ModifiesValidator::setNextValidator(SuchThatValidator nextValidator)
{
    this->nextValidatorInLine = nextValidator;
}

bool ModifiesValidator::isValid(string str)
{
    return false;
}