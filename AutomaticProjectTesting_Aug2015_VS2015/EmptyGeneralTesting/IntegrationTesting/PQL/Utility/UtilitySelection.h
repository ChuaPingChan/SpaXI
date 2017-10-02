#pragma once
#include "..\..\..\SPA\PQL\QueryTree.h"
#include "..\..\..\SPA\PQL\Utilities\SelectClause.h"
#include "..\..\..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\..\SPA\PQL\Utilities\PatternClause.h"

using namespace std;

class UtilitySelection
{
public:
    UtilitySelection();
    ~UtilitySelection();

    static SuchThatClause makeSuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo);
    static SuchThatClause getFirstSuchThatClauseFromTree(QueryTree qt);
    static bool isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual);

    static PatternClause makePatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo);
    static PatternClause makePatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree);
    static PatternClause getFirstPatternClauseFromTree(QueryTree qt);
    static bool isSamePatternClauseContent(PatternClause expected, PatternClause actual);
};
