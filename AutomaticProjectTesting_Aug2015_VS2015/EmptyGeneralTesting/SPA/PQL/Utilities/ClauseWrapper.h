#pragma once

#include "Clause.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "WithClause.h"

/*
    This class acts as a wrapper over the "such that", "pattern" and "with" clauses.
*/
class ClauseWrapper
{
public:
    ClauseWrapper(SuchThatClause &clause);
    ClauseWrapper(PatternClause &clause);
    ClauseWrapper(WithClause &clause);

    bool isSuchThatClause();
    bool isPatternClause();
    bool isWithClause();

    Clause getClause();
    SuchThatClause getSuchThatClause();
    PatternClause getPatternClause();
    WithClause getWithClause();

protected:

    ClauseWrapper();

    enum ClauseCategory
    {
        SUCH_THAT = 0,
        PATTERN = 1,
        WITH = 2
    };

    SuchThatClause *_suchThatClausePtr;
    PatternClause *_patternClausePtr;
    WithClause *_withClausePtr;

    ClauseCategory _clauseCategory;
};
