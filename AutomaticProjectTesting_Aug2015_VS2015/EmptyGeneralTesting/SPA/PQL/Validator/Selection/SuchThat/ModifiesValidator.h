#pragma once
#include "SuchThatValidator.h"

class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator();
    ~ModifiesValidator();

    virtual bool isValid();
};

