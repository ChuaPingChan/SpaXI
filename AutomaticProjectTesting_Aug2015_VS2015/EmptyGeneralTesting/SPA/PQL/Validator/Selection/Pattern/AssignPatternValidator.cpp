#include "AssignPatternValidator.h"

AssignPatternValidator::AssignPatternValidator(string patternType, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, paramStr, qtPtrNew)
{
}


AssignPatternValidator::~AssignPatternValidator()
{
}
