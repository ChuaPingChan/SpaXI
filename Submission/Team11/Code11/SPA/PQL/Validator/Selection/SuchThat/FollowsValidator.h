#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Follows/Follows*
* Assumes the form of Follows(ARGONE, ARGTWO) or Follows*(ARGONE, ARGTWO)
*/
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
    bool isFirstArgValueLessThanSecondArgValue(string argOne, string argTwo);
};
