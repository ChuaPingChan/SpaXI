#pragma once
#include "SuchThatValidator.h"

class FollowsValidator : public SuchThatValidator
{
public:
    FollowsValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~FollowsValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};
