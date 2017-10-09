#pragma once
#include <string>
#include "..\..\..\QueryTree.h"
#include "..\..\..\Attributeship.h"
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

    /*PatternType getPatternType(string str);
    string extractPatternSynonym(string str);
    WithClause makeWithClause();*/

    string extractLhs(string str);
    string extractRhs(string str);

    bool storeInQueryTree(WithClause wc);
};

