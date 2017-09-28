#include "SuchThatClause.h"


SuchThatClause::SuchThatClause(int rel, int type_one, string arg_one, int type_two, string arg_two)
{
	this->rel = rel;
	this->type_one = type_one;
	this->type_two = type_two;
	this->arg_one = arg_one;
	this->arg_two = arg_two;
}

SuchThatClause::~SuchThatClause()
{
}

int SuchThatClause::getRel()
{
	return this->rel;
}

int SuchThatClause::getTypeOne()
{
	return this->type_one;
}

int SuchThatClause::getTypeTwo()
{
	return this->type_two;
}

string SuchThatClause::getArgOne()
{
	return this->arg_one;
}

string SuchThatClause::getArgTwo()
{
	return this->arg_two;
}
