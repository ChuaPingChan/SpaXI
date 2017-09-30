#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(int type, string arg)
{
	this->tuple = false;
	this->selectionType = type;
	this->selectionArg = arg;
}

SelectClause::SelectClause(vector<int> types, vector<string> args)
{
	this->tuple = true;
	this->selectionTypes = types;
	this->selectionArgs = args;
}

SelectClause::~SelectClause()
{
}

bool SelectClause::isTuple()
{
	return tuple;
}

int SelectClause::getSelectionType()
{
	return selectionType;
}

int SelectClause::getSelectionType(int index)
{
	return selectionTypes.at(index);
}

vector<int> SelectClause::getSelectionTypes()
{
	return selectionTypes;
}

string SelectClause::getSelectionArg()
{
	return selectionArg;
}

string SelectClause::getSelectionArg(int index)
{
	return selectionArgs.at(index);
}

vector<string> SelectClause::getSelectionArgs()
{
	return selectionArgs;
}
