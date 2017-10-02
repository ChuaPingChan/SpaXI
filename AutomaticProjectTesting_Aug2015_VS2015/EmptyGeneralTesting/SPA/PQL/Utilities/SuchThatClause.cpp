#include "SuchThatClause.h"


SuchThatClause::SuchThatClause(int rel, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo)
{
	this->_rel = rel;
	this->_argOneType = argOneType;
	this->_argTwoType = argTwoType;
	this->_argOne = argOne;
	this->_argTwo = argTwo;
}

SuchThatClause::~SuchThatClause()
{
}

int SuchThatClause::getRel()
{
	return this->_rel;
}

ENTITY SuchThatClause::getArgOneType()
{
	return this->_argOneType;
}

ENTITY SuchThatClause::getArgTwoType()
{
	return this->_argTwoType;
}

string SuchThatClause::getArgOne()
{
	return this->_argOne;
}

string SuchThatClause::getArgTwo()
{
	return this->_argTwo;
}
