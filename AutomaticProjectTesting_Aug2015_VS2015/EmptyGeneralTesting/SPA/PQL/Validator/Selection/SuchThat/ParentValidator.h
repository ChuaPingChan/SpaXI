#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Parent/Parent*
* Assumes the form of Parent(ARGONE, ARGTWO) or Parent*(ARGONE, ARGTWO)
*/
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
    bool isFirstArgValueLessThanSecondArgValue(string argOne, string argTwo);
};

