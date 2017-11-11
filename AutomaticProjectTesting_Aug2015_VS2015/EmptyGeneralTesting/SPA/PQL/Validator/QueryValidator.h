#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <regex>
#include <algorithm>
#include <functional>
#include "Declaration\DeclarationValidator.h"
#include "Selection\SelectionValidator.h"
#include "..\QueryTree.h"

using namespace std;

/**
 * Checks the overall validation of a query
 * Breaks query into declaration and selection
 * Check validity of individual component
 * Store in QueryTree
 */
class QueryValidator
{
    friend class FriendQueryValidator;                      // Class to be used for testing purposes

public:
    QueryValidator(QueryTree *qtPtrNew);
    ~QueryValidator();

    bool isValidQuery(string query);

private:
    QueryTree *qtPtr;
    DeclarationValidator dv = DeclarationValidator(qtPtr);  // Null when initialised
    SelectionValidator sv = SelectionValidator(qtPtr);      // Null when initialised

    bool isValidDeclarationFlag = true;
    bool isValidSelectionFlag = true;

    bool isValidDeclaration(string str);
    bool isValidSelection(string str);

    vector<string> tokenize(string query);                  // Tokenize with semi-colon as delimiter
    string trim(string query);
};
