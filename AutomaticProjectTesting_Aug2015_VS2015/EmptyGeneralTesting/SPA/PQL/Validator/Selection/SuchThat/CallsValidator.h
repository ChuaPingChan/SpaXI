#pragma once
#include "SuchThatValidator.h"

class CallsValidator : public SuchThatValidator
{
public:
    CallsValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~CallsValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string &argTwo);
};

