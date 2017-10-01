#pragma once
#include <string>
#include <regex>        //TODO:Remove after implementing regex teable
#include "..\..\QueryTree.h"    //TODO: Change to properQueryTree
#include "SuchThat\SuchThatHandler.h"
#include "Pattern\PatternHandler.h"
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

    bool isSuchThat(string str);
    bool isPattern(string str);
};
