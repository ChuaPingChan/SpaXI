#pragma once

#include <unordered_map>
#include <unordered_set>
#include "../Utilities/Clause.h"
#include "../Utilities/SelectClause.h"
#include "../Utilities/SuchThatClause.h"
#include "../Utilities/PatternClause.h"
#include "../Utilities/WithClause.h"

using namespace std;

class ClauseCostCalculator
{
public:

    static const int INF = 2000000000;

    ClauseCostCalculator();

    static int getCost(ClausePtr clausePtr);
    static int getCost(SelectClausePtr selectClausePtr);
    static int getCost(SuchThatClausePtr suchThatClausePtr);
    static int getCost(PatternClausePtr patternClausePtr);
    static int getCost(WithClausePtr withClausePtr);

    // Select-clause will never have cost-relaxation
    static int getRelaxedCost(ClausePtr clausePtr, unordered_set<string> evaluatedSyns);
    static int getRelaxedCost(SuchThatClausePtr suchThatClausePtr, unordered_set<string> evaluatedSyns);
    static int getRelaxedCost(PatternClausePtr patternClausePtr, unordered_set<string> evaluatedSyns);
    static int getRelaxedCost(WithClausePtr withClausePtr, unordered_set<string> evaluatedSyns);

    enum ClauseCost
    {
        // TODO: Consider calculating cost dynamically by querying PKB
        /*
            Static allocation of cost to different clause types

            Assumptions:
            1. Select clause will always have >= 1 synonym, because select
            BOOLEAN will not be added into clause groups
            2. With clause received always has synonyms, because of validator's
            processing
        */

        AFFECTS_1ARG = 90040,
        AFFECTS_2ARGS = 20843250,
        AFFECTS_BOOLEAN = 90000,
        AFFECTS_STAR_1ARG = 20833350,
        AFFECTS_STAR_2ARGS = 20953250,
        AFFECTS_STAR_BOOLEAN = 20833250,
        CALLS_1ARG = 10,
        CALLS_2ARGS = 120,
        CALLS_BOOLEAN = 0,
        CALLS_STAR_1ARG = 30,
        CALLS_STAR_2ARGS = 150,
        CALLS_STAR_BOOLEAN = 0,
        FOLLOWS_1ARG = 501,
        FOLLOWS_2ARGS = 1000,
        FOLLOWS_BOOLEAN = 0,
        FOLLOWS_STAR_1ARG = 1000,
        FOLLOWS_STAR_2ARGS = 50500,
        FOLLOWS_STAR_BOOLEAN = 500,
        MODIFIES_1ARG = 525,
        MODIFIES_2ARGS = 5500,
        MODIFIES_BOOLEAN = 30,
        NEXT_1ARG = 501,
        NEXT_2ARGS = 1000,
        NEXT_BOOLEAN = 0,
        NEXT_STAR_1ARG = 2000,
        NEXT_STAR_2ARGS = 875000,
        NEXT_STAR_BOOLEAN = 1500,
        PARENT_1ARG = 501,
        PARENT_2ARGS = 1000,
        PARENT_BOOLEAN = 50,
        PARENT_STAR_1ARG = 800,
        PARENT_STAR_2ARGS = 2000,
        PARENT_STAR_BOOLEAN = 10,
        PATTERN_ANY_ARGS = 0,
        SELECT_1ARG = 500,
        SELECT_TUPLE = INF,
        USES_1ARG = 550,
        USES_2ARGS = 15500,
        USES_BOOLEAN = 50,
        WITH_ANY_ARGS = 0
    };

private:

};
