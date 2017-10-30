#include <cassert>
#include "SelectClause.h"

SelectClause::SelectClause()
    : Clause(ClauseType::SELECT)
{
}

SelectClause::SelectClause(SelectionType selectionType)
    : Clause(ClauseType::SELECT)
{
    this->selectionType = selectionType;
}

SelectClause::SelectClause(SelectionType selectionType, Entity singleArgType, string singleArg)
    : Clause(ClauseType::SELECT)
{
    this->selectionType = selectionType;
    this->singleArgType = singleArgType;
    this->singleArg = singleArg;

    if (entityIsSynonym(singleArgType))
        addSynonym(singleArg);
}

SelectClause::SelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs)
    : Clause(ClauseType::SELECT)
{
    assert(tupleArgTypes.size() == tupleArgs.size());

    this->selectionType = selectionType;
    this->tupleArgTypes = tupleArgTypes;
    this->tupleArgs = tupleArgs;

    for (int i = 0; i < tupleArgTypes.size(); i++) {
        if (entityIsSynonym(tupleArgTypes[i]))
            addSynonym(tupleArgs[i]);
    }
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
