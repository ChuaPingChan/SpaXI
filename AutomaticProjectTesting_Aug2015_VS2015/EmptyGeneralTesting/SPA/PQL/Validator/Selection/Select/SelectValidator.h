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
    
    bool isValidSelectBoolean(string selectedStr);
    bool isValidSelectSingle(string selectedStr);
    bool isValidSelectTuple(string selectedStr);

    SelectClause makeSelectClause(int selectionType);
    SelectClause makeSelectClause(int selectionType, int singleArgType, string singleArg);
    SelectClause makeSelectClause(int selectionType, vector<int> tupleArgTypes, vector<string> tupleArgs);
   
    bool storeInQueryTree(SelectClause sc);

    int getENTITYOfSynonym(string syn);
    string removeSelectKeyword(string str);
};

