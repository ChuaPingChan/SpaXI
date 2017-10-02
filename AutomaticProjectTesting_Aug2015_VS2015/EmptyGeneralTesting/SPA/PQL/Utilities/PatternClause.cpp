#include "PatternClause.h"


<<<<<<< HEAD
PatternClause::PatternClause(int patternType, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo, ENTITY argThreeType, string argThree)
=======
PatternClause::PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo)
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
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
