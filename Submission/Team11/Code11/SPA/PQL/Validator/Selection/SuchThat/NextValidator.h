#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Next/Next*
* Assumes the form of Next(ARGONE, ARGTWO) or Next*(ARGONE, ARGTWO)
*/
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
