#pragma once
#include "..\..\..\QueryTree.h"
#include "..\..\..\Utilities\SelectClause.h"
#include "..\..\..\..\Entity.h"
#include "..\..\..\Selectionship.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

class SelectValidator
{
public:
    SelectValidator(QueryTree *qtPtrNew);
    ~SelectValidator();

    bool isValid(string str);

private:
    static const int UNKNOWN = -1;
    QueryTree *qtPtr;
    
    bool isValidSelectSingle(string selectedStr);
    bool isValidSelectBoolean(string selectedStr);
    bool isValidSelectTuple(string selectedStr);

    SelectClause makeSelectClause(int selectionType, vector<int> argTypes, vector<string> args);
    SelectClause makeSelectClause(int selectionType);
    bool storeInQueryTree(SelectClause sc);

    int getEntityOfSynonym(string syn);
    string removeSelectKeyword(string str);
};

