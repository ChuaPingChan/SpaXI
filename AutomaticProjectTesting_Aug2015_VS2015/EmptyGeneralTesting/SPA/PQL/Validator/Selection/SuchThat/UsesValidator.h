#pragma once
#include "SuchThatValidator.h"
#include "..\..\..\QueryTreeStub.h"

class UsesValidator : public SuchThatValidator
{
public:
    UsesValidator(QueryTreeStub *qtPtrNew);
    ~UsesValidator();

    virtual void setNextValidator(SuchThatValidator nextValidator);
    virtual bool isValid(string str);

private:
    QueryTreeStub *qtPtr;
    SuchThatValidator nextValidatorInLine;
};

