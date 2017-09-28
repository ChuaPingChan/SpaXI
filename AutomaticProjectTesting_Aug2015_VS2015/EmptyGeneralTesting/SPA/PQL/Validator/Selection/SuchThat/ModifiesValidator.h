#pragma once
#include "SuchThatValidator.h"
#include "..\..\..\QueryTreeStub.h"

class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator(QueryTreeStub *qtPtrNew);
    ~ModifiesValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);
    virtual bool isValid(string str);

private:
    QueryTreeStub *qtPtr;
    SuchThatValidator nextValidatorInLine;
};

