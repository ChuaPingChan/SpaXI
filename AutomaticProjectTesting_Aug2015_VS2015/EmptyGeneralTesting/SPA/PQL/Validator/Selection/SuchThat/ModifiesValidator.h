#pragma once
#include "SuchThatValidator.h"
#include "..\..\..\QueryTree.h"

class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator(QueryTree *qtPtrNew);
    ~ModifiesValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);
    virtual bool isValid(string str);

private:
    QueryTree *qtPtr;
    SuchThatValidator nextValidatorInLine;
};

