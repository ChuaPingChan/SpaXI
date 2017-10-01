#include "PatternValidator.h"

PatternValidator::PatternValidator(int patternType, string paramStr, QueryTree * qtPtrNew)
{
    this->patternType = patternType;
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

int PatternValidator::getPatternType()
{
    return this->patternType;
}

int PatternValidator::getArgOneType()
{
    return this->argOneType;
}

int PatternValidator::getArgTwoType()
{
    return this->argTwoType;
}

int PatternValidator::getArgThreeType()
{
    return this->argThreeType;
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
