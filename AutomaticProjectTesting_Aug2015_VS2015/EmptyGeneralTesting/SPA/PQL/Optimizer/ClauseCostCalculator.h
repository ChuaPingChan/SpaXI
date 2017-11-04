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
        // TODO: Consider calculating cost dynamically by querying PKB
        /*
        Hard assignment of cost to different clause types

        Assumptions:
        1. Select clause will always have >= 1 synonym, because select
        BOOLEAN will not be added into clause groups
        2. With clause received always has synonyms, because of validator's
        processing
        */

        AFFECTS_1ARG = 800000,
        AFFECTS_2ARGS = 1030000,
        AFFECTS_BOOLEAN = 250000,
        AFFECTS_STAR_1ARG = 1000100,
        AFFECTS_STAR_2ARGS = 1120000,
        AFFECTS_STAR_BOOLEAN = 1000000,
        CALLS_1ARG = 20,
        CALLS_2ARGS = 240,
        CALLS_BOOLEAN = 10,
        CALLS_STAR_1ARG = 60,
        CALLS_STAR_2ARGS = 300,
        CALLS_STAR_BOOLEAN = 30,
        FOLLOWS_1ARG = 2,
        FOLLOWS_2ARGS = 1000,
        FOLLOWS_BOOLEAN = 1,
        FOLLOWS_STAR_1ARG = 1000,
        FOLLOWS_STAR_2ARGS = 100000,
        FOLLOWS_STAR_BOOLEAN = 500,
        MODIFIES_1ARG = 60,
        MODIFIES_2ARGS = 10000,
        MODIFIES_BOOLEAN = 30,
        NEXT_1ARG = 2,
        NEXT_2ARGS = 1000,
        NEXT_BOOLEAN = 1,
        NEXT_STAR_1ARG = 200000,
        NEXT_STAR_2ARGS = 500000,
        NEXT_STAR_BOOLEAN = 10000,
        PARENT_1ARG = 2,
        PARENT_2ARGS = 1000,
        PARENT_BOOLEAN = 1,
        PARENT_STAR_1ARG = 20,
        PARENT_STAR_2ARGS = 3000,
        PARENT_STAR_BOOLEAN = 10,
        PATTERN_ANY = 2,
        SELECT_1ARG = 1000,
        SELECT_1ARGS = 1500000,
        USES_1ARG = 100,
        USES_2ARGS = 30000,
        USES_BOOLEAN = 50,
        WITH_ANY = 1
    };

};
