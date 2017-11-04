#pragma once

#include <unordered_map>
#include "../Utilities/Clause.h"

using namespace std;

class ClauseCostCalculator
{
public:
    ClauseCostCalculator();

    static int getCost(ClausePtr clausePtr);

private:

    enum ClauseType
    {
        PATTERN_BOOLEAN = 0,
        FOLLOWS_BOOLEAN,
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
        NEXT_ARGS,
        CALLS_ARGS,
        PARENT_ARGS,
        MODIFIES_ARGS,
        USES_ARGS,
        CALLS_STAR_ARGS,
        PARENT_STAR_ARGS,
        FOLLOWS_STAR_ARGS,

        CALLS_2ARGS,
        CALLS_STAR_2ARGS,
        PARENT_2ARGS,
        MODIFIES_2ARGS,
        USES_2ARGS,
        FOLLOWS_2ARGS,
        PARENT_STAR_2ARGS,
        NEXT_2ARGS,
        FOLLOWS_STAR_2ARGS,

        NEXT_STAR_1ARG,
        NEXT_STAR_2ARGS,
        AFFECTS_1ARG,
        AFFECTS_STAR_1ARG,
        AFFECTS_2ARGS,
        AFFECTS_STAR_2ARGS
    };

    unordered_map<ClauseCostCalculator::ClauseType, int> _costTable;
    
};

