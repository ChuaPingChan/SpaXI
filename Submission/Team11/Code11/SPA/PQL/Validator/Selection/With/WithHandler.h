#pragma once
#include <string>
#include "WithValidator.h"
#include "..\..\..\QueryTree.h"
#include "..\..\..\Utilities\WithClause.h"
#include "..\..\..\Utilities\Formatter.h"

/**
* Checks the validation of with clause
* Wrap into WithClause
* Store WithClause in QueryTree
*/
class WithHandler
{
public:
    WithHandler(QueryTree *qtPtrNew);
    ~WithHandler();

    bool isValidWith(string str);

private:
    QueryTree *qtPtr;

    bool isExactlySameLhsAndRhs(WithValidator wv);

    WithClause makeWithClause(WithValidator withValidator);
    bool storeInQueryTree(WithClause wc);
};
