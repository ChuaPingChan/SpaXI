#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Calls/Calls*
* Assumes the form of Calls(ARGONE, ARGTWO) or Calls*(ARGONE, ARGTWO)
*/
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

