#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(int selectionType)
{
    this->selectionType = selectionType;
}

SelectClause::SelectClause(int selectionType, vector<int> argTypes, vector<string> args)
{
    this->selectionType = selectionType;
    this->argTypes = argTypes;
    this->args = args;
}

SelectClause::~SelectClause()
{
}

int SelectClause::getSelectionType()
{
    return this->selectionType;
}

int SelectClause::getArgTypeAt(int index)
{
	return argTypes.at(index);
}

vector<int> SelectClause::getArgTypes()
{
	return argTypes;
}

string SelectClause::getArgAt(int index)
{
	return args.at(index);
}

vector<string> SelectClause::getArgs()
{
	return args;
}
