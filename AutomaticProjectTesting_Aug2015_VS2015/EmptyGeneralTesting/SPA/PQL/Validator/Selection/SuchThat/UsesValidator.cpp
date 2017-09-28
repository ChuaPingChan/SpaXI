#include "UsesValidator.h"

UsesValidator::UsesValidator(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


UsesValidator::~UsesValidator()
{
}


void UsesValidator::setNextValidator(SuchThatValidator nextValidator)
{
    this->nextValidatorInLine = nextValidator;
}

bool UsesValidator::isValid(string str)
{
    return false;
}