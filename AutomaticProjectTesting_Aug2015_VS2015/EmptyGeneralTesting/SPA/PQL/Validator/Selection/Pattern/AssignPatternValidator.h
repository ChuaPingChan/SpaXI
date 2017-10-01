#pragma once
#include "PatternValidator.h"

class AssignPatternValidator : public PatternValidator
{
public:
    AssignPatternValidator(string patternType, string paramStr, QueryTree *qtPtrNew);
    ~AssignPatternValidator();
};

