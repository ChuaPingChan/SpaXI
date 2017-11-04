#include "ClauseCostCalculator.h"

#include <unordered_map>

ClauseCostCalculator::ClauseCostCalculator()
{
    // TODO: Implement dynamic sorting
    /*
        Hard assignment of cost to different clause types
    */
    _costTable = unordered_map<ClauseCostCalculator::ClauseType, int>(
    {
        { ClauseCostCalculator::ClauseType::PATTERN_BOOLEAN, 1 },
        { ClauseCostCalculator::ClauseType::FOLLOWS_BOOLEAN, 2 },
        { ClauseCostCalculator::ClauseType::NEXT_BOOLEAN, 3 },
        { ClauseCostCalculator::ClauseType::CALLS_BOOLEAN, 4 },
        { ClauseCostCalculator::ClauseType::PARENT_BOOLEAN, 5 },
        { ClauseCostCalculator::ClauseType::MODIFIES_BOOLEAN, 6 },
        { ClauseCostCalculator::ClauseType::USES_BOOLEAN, 7 },
        { ClauseCostCalculator::ClauseType::CALLS_STAR_BOOLEAN, 8 },
        { ClauseCostCalculator::ClauseType::PARENT_STAR_BOOLEAN, 9 },
        { ClauseCostCalculator::ClauseType::FOLLOW_STAR_BOOLEAN, 10 },

        { ClauseCostCalculator::ClauseType::WITH_ANY_ARGS, 11 },
        { ClauseCostCalculator::ClauseType::PATTERN_ANY_ARGS, 12 },
        { ClauseCostCalculator::ClauseType::FOLLOWS_1ARG, 13 },
        { ClauseCostCalculator::ClauseType::NEXT_ARGS, 14 },
        { ClauseCostCalculator::ClauseType::CALLS_ARGS, 15 },
        { ClauseCostCalculator::ClauseType::PARENT_ARGS, 16 },
        { ClauseCostCalculator::ClauseType::MODIFIES_ARGS, 17 },
        { ClauseCostCalculator::ClauseType::USES_ARGS, 18 },
        { ClauseCostCalculator::ClauseType::CALLS_STAR_ARGS, 19 },
        { ClauseCostCalculator::ClauseType::PARENT_STAR_ARGS, 20 },
        { ClauseCostCalculator::ClauseType::FOLLOWS_STAR_ARGS, 21 },

        { ClauseCostCalculator::ClauseType::CALLS_2ARGS, 22 },
        { ClauseCostCalculator::ClauseType::CALLS_STAR_2ARGS, 23 },
        { ClauseCostCalculator::ClauseType::PARENT_2ARGS, 24 },
        { ClauseCostCalculator::ClauseType::MODIFIES_2ARGS, 25 },
        { ClauseCostCalculator::ClauseType::USES_2ARGS, 26 },
        { ClauseCostCalculator::ClauseType::FOLLOWS_2ARGS, 27 },
        { ClauseCostCalculator::ClauseType::PARENT_STAR_2ARGS, 28 },
        { ClauseCostCalculator::ClauseType::NEXT_2ARGS, 29 },
        { ClauseCostCalculator::ClauseType::FOLLOWS_STAR_2ARGS, 30 },

        { ClauseCostCalculator::ClauseType::NEXT_STAR_1ARG, 31 },
        { ClauseCostCalculator::ClauseType::NEXT_STAR_2ARGS, 32 },
        { ClauseCostCalculator::ClauseType::AFFECTS_1ARG, 33 },
        { ClauseCostCalculator::ClauseType::AFFECTS_STAR_1ARG, 34 },
        { ClauseCostCalculator::ClauseType::AFFECTS_2ARGS, 35 },
        { ClauseCostCalculator::ClauseType::AFFECTS_STAR_2ARGS, 36 }
    });
}

int ClauseCostCalculator::getCost(Clause clause)
{
    // TODO: Implement

    Clause::ClauseType clauseType = clause.getClauseType();

    if (clauseType == Clause::ClauseType::SUCH_THAT) {
        
    }
    return 0;
}

int ClauseCostCalculator::getCost(SuchThatClause suchThatClause)
{
    // TODO: Implement
    return 0;
}

int ClauseCostCalculator::getCost(PatternClause patternClause)
{
    // TODO: Implement
    return 0;
}

int ClauseCostCalculator::getCost(WithClause withClause)
{
    // TODO: Implement
    return 0;
}
