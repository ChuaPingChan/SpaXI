#pragma once
#include "PatternValidator.h"

class AssignPatternValidator : public PatternValidator
{
public:
    AssignPatternValidator(int patternType, string paramStr, QueryTree *qtPtrNew);
    ~AssignPatternValidator();
};

