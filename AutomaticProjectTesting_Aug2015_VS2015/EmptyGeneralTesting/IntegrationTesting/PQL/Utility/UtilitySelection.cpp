#include "UtilitySelection.h"


UtilitySelection::UtilitySelection()
{
}


UtilitySelection::~UtilitySelection()
{
}

SuchThatClause UtilitySelection::makeSuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
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
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSameRel && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}


PatternClause UtilitySelection::makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
    //TODO: Might need to create type for unknown
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo);
}

PatternClause UtilitySelection::makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree)
{
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

PatternClause UtilitySelection::getFirstPatternClauseFromTree(QueryTree qt)
{
    vector<PatternClause> pcVector = qt.getPatternClauses();
    return pcVector.front();
}

bool UtilitySelection::isSamePatternClauseAssignWhileContent(PatternClause expected, PatternClause actual)
{
    bool isSamePatternType = expected.getPatternType() == actual.getPatternType();
    bool isSamePatternSyn = expected.getPatternSynonym() == actual.getPatternSynonym();
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSamePatternType && isSamePatternSyn && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}

bool UtilitySelection::isSamePatternClauseIfContent(PatternClause expected, PatternClause actual)
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
