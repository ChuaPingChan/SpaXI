#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(int selectionType)
{
<<<<<<< HEAD
	this->tuple = false;
	this->selectionType = type;
	this->selectionArg = arg;
=======
    this->selectionType = selectionType;
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
}

SelectClause::SelectClause(int selectionType, int singleArgType, string singleArg)
{
<<<<<<< HEAD
	this->tuple = true;
	this->selectionTypes = types;
	this->selectionArgs = args;
=======
    this->selectionType = selectionType;
    this->singleArgType = singleArgType;
    this->singleArg = singleArg;
}

SelectClause::SelectClause(int selectionType, vector<int> tupleArgTypes, vector<string> tupleArgs)
{
    this->selectionType = selectionType;
    this->tupleArgTypes = tupleArgTypes;
    this->tupleArgs = tupleArgs;
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
}

SelectClause::~SelectClause()
{
}

int SelectClause::getSelectionType()
{
    return this->selectionType;
}

<<<<<<< HEAD
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
=======
int SelectClause::getSingleArgType()
{
    return this->singleArgType;
}

string SelectClause::getSingleArg()
{
    return this->singleArg;
}

vector<int> SelectClause::getTupleArgTypes()
{
    return this->tupleArgTypes;
}

int SelectClause::getTupleArgTypeAt(int index)
{
	return tupleArgTypes.at(index);
}

vector<string> SelectClause::getTupleArgs()
{
    return this->tupleArgs;
}

string SelectClause::getTupleArgAt(int index)
{
	return tupleArgs.at(index);
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
}
