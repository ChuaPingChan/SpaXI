#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(int selectionType)
{
    this->selectionType = selectionType;
}

SelectClause::SelectClause(int selectionType, int singleArgType, string singleArg)
{
    this->selectionType = selectionType;
    this->singleArgType = singleArgType;
    this->singleArg = singleArg;
}

SelectClause::SelectClause(int selectionType, vector<int> tupleArgTypes, vector<string> tupleArgs)
{
    this->selectionType = selectionType;
    this->tupleArgTypes = tupleArgTypes;
    this->tupleArgs = tupleArgs;
}

SelectClause::~SelectClause()
{
}

int SelectClause::getSelectionType()
{
    return this->selectionType;
}

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
}
