#include "PatternValidator.h"

const string PatternValidator::ASSIGN = "assign";
const string PatternValidator::WHILE = "while";
const string PatternValidator::IF = "if";

const string PatternValidator::VARIABLE = "variable";
const string PatternValidator::UNDERSCORE = "underscore";
const string PatternValidator::IDENT_WITH_QUOTES = "ident";
const string PatternValidator::EXPRESSION_SPEC = "expression_spec";

PatternValidator::PatternValidator(string patternType, string paramStr, QueryTree * qtPtrNew)
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

string PatternValidator::getPatternType()
{
    return this->patternType;
}

string PatternValidator::getArgOneType()
{
    return this->argOneType;
}

string PatternValidator::getArgTwoType()
{
    return this->argTwoType;
}

string PatternValidator::getArgThreeType()
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
