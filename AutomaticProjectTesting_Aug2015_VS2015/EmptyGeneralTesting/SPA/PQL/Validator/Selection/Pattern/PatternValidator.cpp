#include "PatternValidator.h"

const string PatternValidator::PATTERN_KEYWORD = "pattern";


PatternValidator::PatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree * qtPtrNew)
{
    this->patternType = patternType;
    this->patternSyn = patternSyn;
    this->paramStr = paramStr;
    this->qtPtr = qtPtrNew;
}

PatternValidator::~PatternValidator()
{
}

void PatternValidator::validate()
{
}

bool PatternValidator::isValid()
{
    return this->validity;
}

PatternType PatternValidator::getPatternType()
{
    return this->patternType;
}

Entity PatternValidator::getArgOneType()
{
    return this->argOneType;
}

Entity PatternValidator::getArgTwoType()
{
    return this->argTwoType;
}

Entity PatternValidator::getArgThreeType()
{
    return this->argThreeType;
}

string PatternValidator::getPatternSynonym()
{
    return this->patternSyn;
}

string PatternValidator::getArgOne()
{
    return this->argOne;
}

string PatternValidator::getArgTwo()
{
    return this->argTwo;
}

string PatternValidator::getArgThree()
{
    return this->argThree;
}
