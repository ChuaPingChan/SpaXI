#pragma once
#include "PatternValidator.h"

class WhilePatternValidator : public PatternValidator
{
public:
    WhilePatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew);
    ~WhilePatternValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string argTwo);

    string extractArgOne(string str);
    string extractArgTwo(string str);
};
