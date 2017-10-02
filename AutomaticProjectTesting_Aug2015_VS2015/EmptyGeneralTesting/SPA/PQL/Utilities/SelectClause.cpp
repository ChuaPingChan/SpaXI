#include "SelectClause.h"

SelectClause::SelectClause()
{
}

SelectClause::SelectClause(SelectionType selectionType)
{
    this->selectionType = selectionType;
}

SelectClause::SelectClause(SelectionType selectionType, Entity singleArgType, string singleArg)
{
    this->selectionType = selectionType;
    this->singleArgType = singleArgType;
    this->singleArg = singleArg;
}

SelectClause::SelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs)
{
    this->selectionType = selectionType;
    this->tupleArgTypes = tupleArgTypes;
    this->tupleArgs = tupleArgs;
}

SelectClause::~SelectClause()
{
}

SelectionType SelectClause::getSelectionType()
{
    return this->selectionType;
}

Entity SelectClause::getSingleArgType()
{
    return this->singleArgType;
}

string SelectClause::getSingleArg()
{
    return this->singleArg;
}

vector<Entity> SelectClause::getTupleArgTypes()
{
    return this->tupleArgTypes;
}

Entity SelectClause::getTupleArgTypeAt(int index)
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
