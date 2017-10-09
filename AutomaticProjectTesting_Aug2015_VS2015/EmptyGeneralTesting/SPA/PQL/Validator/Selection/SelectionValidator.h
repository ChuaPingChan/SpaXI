#pragma once
#include <string>
#include <regex>        //TODO:Remove after implementing regex teable
#include "..\..\QueryTree.h"
#include "Select\SelectValidator.h"
#include "SuchThat\SuchThatHandler.h"
#include "Pattern\PatternHandler.h"
#include "With\WithHandler.h"
#include "..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

class SelectionValidator
{
public:
    SelectionValidator(QueryTree *qtPtrNew);
    ~SelectionValidator();

    bool isValidSelection(string str);
    bool setQueryTree(QueryTree *qtPtrNew);

    

private:
    QueryTree *qtPtr;

    bool isValidSelect(string str);
    bool areValidClauses(string str);

    bool isSuchThat(string str);
    bool isPattern(string str);
    bool isWith(string str);

    string extractSelectRawStr(string str);
};
