#pragma once
#include "PatternValidator.h"

/** 
 * Semantic Validation of Pattern-Assign
 * Assumes the form of ASSIGN(ARGONE, ARGTWO)
 */
class AssignPatternValidator : public PatternValidator
{
public:
    AssignPatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew);
    ~AssignPatternValidator();

    void validate();
    bool isValid();

private:
    bool isValidArgOne(string &argOne);
    bool isValidArgTwo(string &argTwo);

    string extractArgOne(string str);
    string extractArgTwo(string str);

    bool isWellFormExpr(string str);        // Check if a given expression is well-formed by counting number of brackets
};

