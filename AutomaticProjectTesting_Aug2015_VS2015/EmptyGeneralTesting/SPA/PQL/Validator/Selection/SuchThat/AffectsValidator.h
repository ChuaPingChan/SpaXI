#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Affects/Affects*
* Assumes the form of Affects(ARGONE, ARGTWO) or Affects*(ARGONE, ARGTWO)
*/
class AffectsValidator : public SuchThatValidator
{
public:
    AffectsValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~AffectsValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};

