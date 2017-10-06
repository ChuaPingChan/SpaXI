#pragma once
#include "SuchThatValidator.h"

class ParentValidator : public SuchThatValidator
{
public:
    ParentValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~ParentValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};

