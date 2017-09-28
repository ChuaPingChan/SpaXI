#include "PatternClause.h"


PatternClause::PatternClause(int type, int type_one, string arg_one, int type_two, string arg_two, int type_three, string arg_three)
{
	this->type = type;
	this->type_one = type_one;
	this->type_two = type_two;
	this->type_three = type_three;
	this->arg_one = arg_one;
	this->arg_two = arg_two;
	this->arg_three = arg_three;
}

PatternClause::~PatternClause()
{
}

int PatternClause::getType()
{
	return type;
}

int PatternClause::getTypeOne()
{
	return this->type_one;
}

int PatternClause::getTypeTwo()
{
	return this->type_two;
}

int PatternClause::getTypeThree()
{
	return this->type_three;
}

string PatternClause::getArgOne()
{
	return this->arg_one;
}

string PatternClause::getArgTwo()
{
	return this->arg_two;
}

string PatternClause::getArgThree()
{
	return this->arg_three;
}
