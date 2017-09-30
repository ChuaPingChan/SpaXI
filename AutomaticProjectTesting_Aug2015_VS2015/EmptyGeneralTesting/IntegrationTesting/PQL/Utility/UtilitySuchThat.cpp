#include "UtilitySuchThat.h"


UtilitySuchThat::UtilitySuchThat()
{
}


UtilitySuchThat::~UtilitySuchThat()
{
}

SuchThatClause UtilitySuchThat::makeSuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo)
{
    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

SuchThatClause UtilitySuchThat::getFirstClauseFromTree(QueryTree qt)
{
    vector<SuchThatClause> stcVector = qt.getSuchThatClauses();
    return stcVector.front();
}

bool UtilitySuchThat::isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual)
{
    bool isSameRel = expected.getRel() == actual.getRel();
    bool isSameArgOneType = expected.getTypeOne() == actual.getTypeOne();
    bool isSameArgTwoType = expected.getTypeTwo() == actual.getTypeTwo();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSameRel && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}
