#pragma once
#include "PatternValidator.h"

/**
* Semantic Validation of Pattern-If
* Assumes the form of IF(ARGONE, ARGTWO, ARGTHREE)
*/
class IfPatternValidator : public PatternValidator
{
public:
    IfPatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew);
    ~IfPatternValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string argTwo);
    bool isValidArgThree(string argThree);

    string extractArgOne(string str);
    string extractArgTwo(string str);
    string extractArgThree(string str);
};
