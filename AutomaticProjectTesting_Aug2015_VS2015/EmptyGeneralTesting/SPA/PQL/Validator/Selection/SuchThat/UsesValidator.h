#pragma once
#include "SuchThatValidator.h"
#include "..\..\..\QueryTree.h"

class UsesValidator : public SuchThatValidator
{
public:
    UsesValidator(QueryTree *qtPtrNew);
    ~UsesValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);
    virtual bool isValid(string str);

private:
    QueryTree *qtPtr;
    SuchThatValidator nextValidatorInLine;
};

