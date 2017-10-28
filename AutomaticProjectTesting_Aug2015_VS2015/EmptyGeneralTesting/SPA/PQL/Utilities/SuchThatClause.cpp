#include "SuchThatClause.h"
#include "../../Entity.h"


SuchThatClause::SuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
	this->_rel = rel;
	this->_argOneType = argOneType;
	this->_argTwoType = argTwoType;
	this->_argOne = argOne;
	this->_argTwo = argTwo;

    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
    if (entityIsSynonym(argTwoType)) {
        addSynonym(argTwo);
    }
}

SuchThatClause::~SuchThatClause()
{
}

Relationship SuchThatClause::getRel()
{
	return this->_rel;
}

Entity SuchThatClause::getArgOneType()
{
	return this->_argOneType;
}

Entity SuchThatClause::getArgTwoType()
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
