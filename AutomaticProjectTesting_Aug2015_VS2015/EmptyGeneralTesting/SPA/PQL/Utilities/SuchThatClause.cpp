#include "SuchThatClause.h"


SuchThatClause::SuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo)
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

int SuchThatClause::getArgOneType()
{
	return this->_argOneType;
}

int SuchThatClause::getArgTwoType()
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
