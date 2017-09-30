#pragma once
#include "..\..\..\SPA\PQL\QueryTree.h"
#include "..\..\..\SPA\PQL\Utilities\SelectClause.h"
#include "..\..\..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\..\SPA\PQL\Utilities\PatternClause.h"

class UtilitySuchThat
{
public:
    UtilitySuchThat();
    ~UtilitySuchThat();

    static SuchThatClause makeSuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo);

    static SuchThatClause getFirstClauseFromTree(QueryTree qt);
    static bool isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual);
};

