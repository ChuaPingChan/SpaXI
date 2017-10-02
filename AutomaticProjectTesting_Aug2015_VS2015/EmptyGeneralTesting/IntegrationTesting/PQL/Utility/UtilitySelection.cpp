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

SuchThatClause UtilitySelection::getFirstSuchThatClauseFromTree(QueryTree qt)
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


PatternClause UtilitySelection::makePatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo)
{
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo, -1, "");
}

PatternClause UtilitySelection::makePatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree)
{
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

PatternClause UtilitySelection::getFirstPatternClauseFromTree(QueryTree qt)
{
    vector<PatternClause> pcVector = qt.getPatternClauses();
    return pcVector.front();
}

bool UtilitySelection::isSamePatternClauseContent(PatternClause expected, PatternClause actual)
{
    bool isSamePatternType = expected.getPatternType() == actual.getPatternType();
    bool isSamePatternSyn = expected.getPatternSynonym() == actual.getPatternSynonym();
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgThreeType = expected.getArgThreeType() == actual.getArgThreeType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();
    bool isSameArgThree = expected.getArgThree() == actual.getArgThree();

    return isSamePatternType && isSamePatternSyn && isSameArgOneType && isSameArgTwoType && isSameArgThreeType && isSameArgOne && isSameArgTwo && isSameArgThree;
}
