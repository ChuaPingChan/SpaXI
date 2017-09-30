#pragma once
#include "SuchThatValidator.h"

class ModifiesValidator : public SuchThatValidator
{
public:
    ModifiesValidator(string rel, string str);
    ~ModifiesValidator();

    void validate();
    bool isValid();
    
private:
    string paramStr;

    bool isValidArgOne(string argOne);
    bool isValidArgTwo(string argTwo);
};
