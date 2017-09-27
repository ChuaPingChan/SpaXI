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
    QueryValidator();
    ~QueryValidator();

    bool isValidQuery(string query);

private:
    DeclarationValidator dv;
    SelectionValidator sv;

    bool isValidDeclaration(string str);
    bool isValidSelection(string str);

    vector<string> tokenize(string query);
};
