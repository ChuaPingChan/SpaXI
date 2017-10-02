#include "UsesValidator.h"

UsesValidator::UsesValidator(QueryTree *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


UsesValidator::~UsesValidator()
{
}

bool UsesValidator::isValid(string str)
{
    return false;
}