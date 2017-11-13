#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Uses
* Assumes the form of Uses(ARGONE, ARGTWO)
*/
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

