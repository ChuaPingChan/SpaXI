#include "PatternClause.h"


PatternClause::PatternClause(int patternType, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree)
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
