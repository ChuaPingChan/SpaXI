#pragma once
#include "..\..\..\QueryTree.h"
#include "..\..\..\Utilities\SelectClause.h"
#include "..\..\..\..\Entity.h"
#include "..\..\..\Selectionship.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\..\Exceptions\SynonymNotFoundException.h"

using namespace std;

class SelectValidator
{
public:
    SelectValidator(QueryTree *qtPtrNew);
    ~SelectValidator();

    bool isValid(string str);

private:
    QueryTree *qtPtr;
    
    bool isValidSelectBoolean(string selectedStr);
    bool isValidSelectSingle(string selectedStr);
    bool isValidSelectTuple(string selectedStr);

    SelectClause makeSelectClause(SelectionType selectionType);
    SelectClause makeSelectClause(SelectionType selectionType, Entity singleArgType, string singleArg);
    SelectClause makeSelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs);
   
    bool storeInQueryTree(SelectClause sc);

    Entity getEntityOfSynonym(string syn);
    bool isKnownEntity(Entity entity);  //TODO: Remove after throwing exception
    string removeSelectKeyword(string str);
};

