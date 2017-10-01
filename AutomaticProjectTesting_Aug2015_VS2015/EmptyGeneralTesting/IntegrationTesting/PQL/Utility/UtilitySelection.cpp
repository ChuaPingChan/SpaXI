#include "UtilitySelection.h"


UtilitySelection::UtilitySelection()
{
}


UtilitySelection::~UtilitySelection()
{
}

SuchThatClause UtilitySelection::makeSuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo)
{
    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

PatternClause UtilitySelection::makePatternClause(int patternType, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree)
{
    return PatternClause(patternType, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

SuchThatClause UtilitySelection::getFirstClauseFromTree(QueryTree qt)
{
    vector<SuchThatClause> stcVector = qt.getSuchThatClauses();
    return stcVector.front();
}

bool UtilitySelection::isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual)
{
    bool isSameRel = expected.getRel() == actual.getRel();
    bool isSameArgOneType = expected.getTypeOne() == actual.getTypeOne();
    bool isSameArgTwoType = expected.getTypeTwo() == actual.getTypeTwo();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSameRel && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}
