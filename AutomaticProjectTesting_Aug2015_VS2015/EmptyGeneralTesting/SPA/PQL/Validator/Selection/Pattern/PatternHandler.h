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
#include "..\..\..\..\Exceptions\SynonymNotFoundException.h"

/**
 * Checks the validation of pattern clause
 * Wrap into PatternClause
 * Store PatternClause in QueryTree
 */
class PatternHandler
{
public:
    PatternHandler(QueryTree *qtPtrNew);
    ~PatternHandler();

    bool isValidPattern(string str);

private:
    QueryTree *qtPtr;

    PatternType getPatternType(string str);                 // Get mapping of synonym to its pattern type

    string extractPatternSynonym(string str);               // Get synonym that determines pattern type

    PatternClause makePatternClause(PatternValidator pv);
    bool storeInQueryTree(PatternClause pc);
};
