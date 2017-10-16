#pragma once
#include <string>
#include "..\..\..\QueryTree.h"
#include "..\..\..\Patternship.h"
#include "..\..\..\..\Entity.h"
#include "PatternValidator.h"
#include "AssignPatternValidator.h"
#include "WhilePatternValidator.h"
#include "IfPatternValidator.h"
#include "..\..\..\Utilities\PatternClause.h"
#include "..\..\..\Utilities\Formatter.h"

class PatternHandler
{
public:
    PatternHandler(QueryTree *qtPtrNew);
    ~PatternHandler();

    bool isValidPattern(string str);

private:
    QueryTree *qtPtr;

    PatternType getPatternType(string str);

    string extractPatternSynonym(string str);

    PatternClause makePatternClause(PatternValidator pv);
    bool storeInQueryTree(PatternClause pc);
};
