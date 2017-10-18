#pragma once
#include "SuchThatValidator.h"

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

