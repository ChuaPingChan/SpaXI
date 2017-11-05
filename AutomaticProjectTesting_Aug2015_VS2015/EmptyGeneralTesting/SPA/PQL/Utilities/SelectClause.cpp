#include <cassert>
#include "SelectClause.h"
#include "Clause.h"

SelectClause::SelectClause()
    : Clause(Clause::ClauseType::SELECT)
{
}

SelectClause::SelectClause(SelectionType selectionType)
    : Clause(Clause::ClauseType::SELECT)
{
    this->selectionType = selectionType;
}

SelectClause::SelectClause(SelectionType selectionType, Entity singleArgType, string singleArg)
    : Clause(Clause::ClauseType::SELECT)
{
    this->selectionType = selectionType;
    this->singleArgType = singleArgType;
    this->singleArg = singleArg;
    this->isAttributeProcName = false;

    if (entityIsSynonym(singleArgType))
        addSynonym(singleArg);
}

SelectClause::SelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs)
    : Clause(Clause::ClauseType::SELECT)
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

SelectClausePtr SelectClause::getSharedPtr()
{
    SelectionType selectionType = getSelectionType();

    if (selectionType == SelectionType::SELECT_BOOLEAN) {
        return SelectClausePtr(new SelectClause(selectionType));
    } else if (selectionType == SelectionType::SELECT_SINGLE) {
        return SelectClausePtr(new SelectClause(selectionType, getSingleArgType(), getSingleArg()));
    } else {
        return SelectClausePtr(new SelectClause(selectionType, getTupleArgTypes(), getTupleArgs()));
    }
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
