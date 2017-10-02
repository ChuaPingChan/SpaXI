#include "PatternClause.h"

using namespace std;

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;
}

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree)
{
    PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo);
    this->_argThreeType = argThreeType;
    this->_argThree = argThree;
}

PatternClause::~PatternClause()
{
}

PatternType PatternClause::getPatternType()
{
    return _patternType;
}

Entity PatternClause::getArgOneType()
{
    return this->_argOneType;
}

Entity PatternClause::getArgTwoType()
{
    return this->_argTwoType;
}

Entity PatternClause::getArgThreeType()
{
    return this->_argThreeType;
}

string PatternClause::getPatternSynonym()
{
    return this->_patternSyn;
}

string PatternClause::getArgOne()
{
    return this->_argOne;
}

string PatternClause::getArgTwo()
{
    return this->_argTwo;
}

string PatternClause::getArgThree()
{
    return this->_argThree;
}
