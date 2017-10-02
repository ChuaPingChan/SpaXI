#include "PatternClause.h"


PatternClause::PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;
}

PatternClause::PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree)
{
    PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo);
    this->_argThreeType = argThreeType;
    this->_argThree = argThree;
}

PatternClause::~PatternClause()
{
}

int PatternClause::getPatternType()
{
	return _patternType;
}

int PatternClause::getArgOneType()
{
	return this->_argOneType;
}

int PatternClause::getArgTwoType()
{
	return this->_argTwoType;
}

int PatternClause::getArgThreeType()
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
