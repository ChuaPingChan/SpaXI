#pragma once
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <memory>
#include "../../Entity.h"
#include "../Selectionship.h"
#include "Clause.h"

using namespace std;

class SelectClause : public Clause
{
public:
    SelectClause();
    SelectClause(SelectionType selectionType);
    SelectClause(SelectionType selectionType, Entity singleArgType, string singleArg);
    SelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs);
    ~SelectClause();

    /* Getters */
    SelectionType getSelectionType();

    Entity getSingleArgType();
    string getSingleArg();

    vector<Entity> getTupleArgTypes();
    Entity getTupleArgTypeAt(int index);
    
    vector<string> getTupleArgs();
    string getTupleArgAt(int index);

    bool isAttributeProcName = false;
    vector<bool> isAttributeProcNameForTuple;

private:

    SelectionType selectionType;
    Entity singleArgType;
    string singleArg;
    vector<Entity> tupleArgTypes;
    vector<string> tupleArgs;
};

typedef shared_ptr<SelectClause> SelectClausePtr;
