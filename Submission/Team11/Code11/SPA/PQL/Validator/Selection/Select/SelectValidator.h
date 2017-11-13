#pragma once
#include "..\..\..\QueryTree.h"
#include "..\..\..\Utilities\SelectClause.h"
#include "..\..\..\..\Entity.h"
#include "..\..\..\Selectionship.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\..\Exceptions\SynonymNotFoundException.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include <string>

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

    bool isValidAttrRefForSynonym(string str);
    bool isProcNameAttribute(string attribute);
    bool isStmtNumAttribute(string attribute);
    bool isVarNameAttribute(string attribute);
    bool isValueAttribute(string attribute);

    string removeSelectKeyword(string str);
    string removeSpecialCharactersFromTuple(string selectedStr);
    vector<string> splitSynonymAttribute(string selectedStr);
    vector<string> extractSynonymsFromTuple(string formattedStr);
};

