#pragma once
#include <string>
#include "WithValidator.h"
#include "..\..\..\QueryTree.h"
#include "..\..\..\Utilities\WithClause.h"
#include "..\..\..\Utilities\Formatter.h"

class WithHandler
{
public:
    WithHandler(QueryTree *qtPtrNew);
    ~WithHandler();

    bool isValidWith(string str);

private:
    QueryTree *qtPtr;

    WithClause makeWithClause(WithValidator withValidator);

    bool storeInQueryTree(WithClause wc);
};
