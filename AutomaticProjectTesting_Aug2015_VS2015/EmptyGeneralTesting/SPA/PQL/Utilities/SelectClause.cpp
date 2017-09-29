#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(int type, string arg)
{
	this->tuple = false;
	this->type = type;
	this->arg = arg;
}

SelectClause::SelectClause(vector<int> types, vector<string> args)
{
	this->tuple = true;
	this->types = types;
	this->args = args;
}

SelectClause::~SelectClause()
{
}

bool SelectClause::isTuple()
{
	return tuple;
}

int SelectClause::getType()
{
	return type;
}

int SelectClause::getType(int index)
{
	return types.at(index);
}

vector<int> SelectClause::getTypes()
{
	return types;
}

string SelectClause::getArg()
{
	return arg;
}

string SelectClause::getArg(int index)
{
	return args.at(index);
}

vector<string> SelectClause::getArgs()
{
	return args;
}
