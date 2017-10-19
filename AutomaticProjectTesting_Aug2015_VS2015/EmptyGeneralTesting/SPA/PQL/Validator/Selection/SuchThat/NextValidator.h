#pragma once
#include "SuchThatValidator.h"

class NextValidator : public SuchThatValidator
{
public:
    NextValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~NextValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};
