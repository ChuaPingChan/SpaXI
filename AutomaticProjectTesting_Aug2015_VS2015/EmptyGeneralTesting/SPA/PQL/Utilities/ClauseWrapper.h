#pragma once

#include <memory>
#include "Clause.h"
#include "SelectClause.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "WithClause.h"

/*
    This class acts as a wrapper over the "such that", "pattern" and "with" clauses.
*/
class ClauseWrapper
{
public:
    ClauseWrapper(SelectClause &clause);
    ClauseWrapper(SuchThatClause &clause);
    ClauseWrapper(PatternClause &clause);
    ClauseWrapper(WithClause &clause);
    ~ClauseWrapper();

    bool isSelectClause();
    bool isSuchThatClause();
    bool isPatternClause();
    bool isWithClause();

    Clause getClause();
    SelectClause getSelectClause();
    SuchThatClause getSuchThatClause();
    PatternClause getPatternClause();
    WithClause getWithClause();

protected:

    ClauseWrapper();

    enum ClauseCategory
    {
        SELECT = 0,
        SUCH_THAT = 1,
        PATTERN = 2,
        WITH = 3
    };

    SelectClause *_selectClausePtr;
    SuchThatClause *_suchThatClausePtr;
    PatternClause *_patternClausePtr;
    WithClause *_withClausePtr;

    ClauseCategory _clauseCategory;
};
