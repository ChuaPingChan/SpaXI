#pragma once
#include <string>
#include "..\..\..\QueryTree.h"
#include "..\..\..\Patternship.h"
#include "PatternValidator.h"
#include "AssignPatternValidator.h"
#include "WhilePatternValidator.h"
#include "IfPatternValidator.h"
#include "..\..\..\Utilities\PatternClause.h"
#include "..\..\..\Utilities\Formatter.h"

class PatternHandler
{
public:
    static const string ASSIGN;
    static const string WHILE;
    static const string IF;

    PatternHandler(QueryTree *qtPtrNew);
    ~PatternHandler();

    bool isValidPattern(string str);

private:
    static const string PATTERN_KEYWORD;
    QueryTree *qtPtr;

    int getPatternType(string str);

    string extractArgOne(string str);

    bool isArgumentInClause(string arg, unordered_set<string> clause);

    PatternClause makePatternClause(PatternValidator pv);
    bool storeInQueryTree(PatternClause pc);
};
