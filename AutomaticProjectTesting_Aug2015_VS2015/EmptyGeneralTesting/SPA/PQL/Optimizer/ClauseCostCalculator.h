#pragma once

#include <unordered_map>
#include "../Utilities/Clause.h"
#include "../Utilities/SelectClause.h"
#include "../Utilities/SuchThatClause.h"
#include "../Utilities/PatternClause.h"
#include "../Utilities/WithClause.h"

using namespace std;

class ClauseCostCalculator
{
public:
    ClauseCostCalculator();

    static int getCost(ClausePtr clausePtr);
    static int getCost(SelectClausePtr selectClausePtr);
    static int getCost(SuchThatClausePtr suchThatClausePtr);
    static int getCost(PatternClausePtr patternClausePtr);
    static int getCost(WithClausePtr withClausePtr);

private:

    enum ClauseCost
    {
        // TODO: Implement dynamic sorting
        /*
        Hard assignment of cost to different clause types

        Assumptions:
        1. Select clause will always have >= 1 synonym, because select
        BOOLEAN will not be added into clause groups
        2. With clause received always has synonyms, because of validator's
        processing
        */

        FOLLOWS_BOOLEAN = 0,
        NEXT_BOOLEAN,
        CALLS_BOOLEAN,
        PARENT_BOOLEAN,
        MODIFIES_BOOLEAN,
        USES_BOOLEAN,
        CALLS_STAR_BOOLEAN,
        PARENT_STAR_BOOLEAN,
        FOLLOW_STAR_BOOLEAN,

        WITH_ANY_ARGS,
        PATTERN_ANY_ARGS,
        FOLLOWS_1ARG,
        NEXT_1ARG,
        CALLS_1ARG,
        CALLS_STAR_1ARG,
        PARENT_1ARG,
        MODIFIES_1ARG,
        USES_1ARG,
        SELECT_1ARG,
        PARENT_STAR_1ARG,
        FOLLOWS_STAR_1ARG,

        CALLS_2ARGS,
        CALLS_STAR_2ARGS,
        PARENT_2ARGS,
        MODIFIES_2ARGS,
        USES_2ARGS,
        FOLLOWS_2ARGS,
        PARENT_STAR_2ARGS,
        NEXT_2ARGS,
        FOLLOWS_STAR_2ARGS,

        NEXT_STAR_BOOLEAN,
        NEXT_STAR_1ARG,
        AFFECTS_BOOLEAN,
        NEXT_STAR_2ARGS,
        AFFECTS_1ARG,
        AFFECTS_STAR_BOOLEAN,
        AFFECTS_STAR_1ARG,
        AFFECTS_2ARGS,
        AFFECTS_STAR_2ARGS,

        SELECT_TUPLE
    };

};
