#pragma once
#include "SuchThatValidator.h"

class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator(string rel, string paramStr, QueryTree *qtPtrNew);
    ~ModifiesValidator();

    void validate();
    bool isValid();
    
private:
    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};
