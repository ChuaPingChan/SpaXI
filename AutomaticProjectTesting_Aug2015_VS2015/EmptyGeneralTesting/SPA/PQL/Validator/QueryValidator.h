#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <regex>
#include <algorithm>
#include "Declaration\DeclarationValidator.h"
#include "Selection\SelectionValidator.h"
#include "..\QueryTree.h"

using namespace std;

class QueryValidator
{
public:
    QueryValidator(QueryTree *qtPtrNew);
    ~QueryValidator();

    bool isValidQuery(string query);

private:
    QueryTree *qtPtr;
    DeclarationValidator dv = DeclarationValidator(qtPtr);  //Null when initialised
    SelectionValidator sv = SelectionValidator(qtPtr);      //Null when initialised

    bool isValidDeclaration(string str);
    bool isValidSelection(string str);

    vector<string> tokenize(string query);
};
