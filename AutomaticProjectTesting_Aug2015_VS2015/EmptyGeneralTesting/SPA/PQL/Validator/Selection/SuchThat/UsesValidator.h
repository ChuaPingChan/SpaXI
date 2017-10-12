#pragma once
#include "SuchThatValidator.h"

class UsesValidator : public SuchThatValidator
{
public:
    UsesValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~UsesValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string &argTwo);
};

