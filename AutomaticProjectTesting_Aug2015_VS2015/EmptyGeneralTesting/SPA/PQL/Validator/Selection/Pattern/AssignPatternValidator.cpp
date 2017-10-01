#include "AssignPatternValidator.h"

AssignPatternValidator::AssignPatternValidator(int patternType, string paramStr, QueryTree *qtPtrNew)
    :PatternValidator(patternType, paramStr, qtPtrNew)
{
}


AssignPatternValidator::~AssignPatternValidator()
{
}
