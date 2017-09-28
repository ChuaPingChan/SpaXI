#pragma once
#include <string>
#include "..\..\QueryTree.h"

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
};
