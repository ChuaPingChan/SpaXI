#pragma once
#include <string>
#include "..\..\QueryTree.h"
#include "Select\SelectValidator.h"
#include "SuchThat\SuchThatHandler.h"
#include "Pattern\PatternHandler.h"
#include "With\WithHandler.h"
#include "..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

/**
* Checks the overall selection validation of a query
* Breaks query into clauses
* Check validity of individual clause
* Store in QueryTree
*/
class SelectionValidator
{
    friend class FriendSelectionValidator;          // Class to be used for testing purposes
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
