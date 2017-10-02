#include "PatternClause.h"


PatternClause::PatternClause(int patternType, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo, ENTITY argThreeType, string argThree)
{
	this->_patternType = patternType;
	this->_argOneType = argOneType;
	this->_argTwoType = argTwoType;
	this->_argThreeType = argThreeType;
	this->_argOne = argOne;
	this->_argTwo = argTwo;
	this->_argThree = argThree;
}

PatternClause::~PatternClause()
{
}

int PatternClause::getPatternType()
{
	return _patternType;
}

ENTITY PatternClause::getArgOneType()
{
	return this->_argOneType;
}

ENTITY PatternClause::getArgTwoType()
{
	return this->_argTwoType;
}

ENTITY PatternClause::getArgThreeType()
{
	return this->_argThreeType;
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
