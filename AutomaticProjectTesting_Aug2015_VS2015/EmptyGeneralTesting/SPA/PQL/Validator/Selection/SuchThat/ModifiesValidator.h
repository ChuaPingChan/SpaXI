#pragma once
#include "SuchThatValidator.h"

/**
* Semantic Validation of SuchThat-Modifies
* Assumes the form of Modifies(ARGONE, ARGTWO)
*/
class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    ~ModifiesValidator();

    void validate();
    bool isValid();
    
private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string &argTwo);
};
