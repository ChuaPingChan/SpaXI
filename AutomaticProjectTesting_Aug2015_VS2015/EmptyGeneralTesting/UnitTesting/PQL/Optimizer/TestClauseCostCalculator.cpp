#include "CppUnitTest.h"
#include <string>
#include <list>

#include "../SPA/PQL/Optimizer/ClauseCostCalculator.h"
#include "../SPA/PQL/Utilities/SelectClause.h"
#include "../SPA/PQL/Utilities/SuchThatClause.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseCostCalculator)
    {
    public:

        TEST_METHOD(TestGetCost) {

            /**********
             * Set up *
             **********/
            /*
                Query:
                assign a1, a2; stmt s1, s2;
                while w1, w2; if i1, if2; while w1, w2; call cl1, cl2;
                procedure p1, p2; prog_line pl1, pl2;
                variable v1, v2; constant c1, c2;

                Select a1
                such that Uses(a1, v1)
                such that Modifies(w1, v1)
                such that Uses(a2, v2)
                such that Uses(10, "dummyVar")
            */

            SelectClause select_a1 = SelectClause(SelectionType::SELECT_SINGLE, Entity::ASSIGN, "a1");
            SuchThatClause uses_a1_v1 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");
            SuchThatClause modifies_w1_v1 = SuchThatClause(Relationship::MODIFIES,
                Entity::WHILE, "w1",
                Entity::VARIABLE, "v1");
            SuchThatClause uses_a2_v2 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a2",
                Entity::VARIABLE, "v2");
            SuchThatClause uses_10_ident = SuchThatClause(Relationship::USES,
                Entity::INTEGER, "10",
                Entity::IDENT_WITHQUOTES, "dummyVar");

            /***********
             * Testing *
             ***********/
            int actualCost;
            int expectedCost;

            actualCost = ClauseCostCalculator::getCost(select_a1.getSharedPtr());
            expectedCost = ClauseCost::SELECT_1ARG;
            Assert::IsTrue(actualCost == expectedCost);

            actualCost = ClauseCostCalculator::getCost(uses_a1_v1.getSharedPtr());
            expectedCost = ClauseCost::USES_2ARGS;
            Assert::IsTrue(actualCost == expectedCost);

            actualCost = ClauseCostCalculator::getCost(modifies_w1_v1.getSharedPtr());
            expectedCost = ClauseCost::MODIFIES_2ARGS;
            Assert::IsTrue(actualCost == expectedCost);

            actualCost = ClauseCostCalculator::getCost(uses_10_ident.getSharedPtr());
            expectedCost = ClauseCost::USES_BOOLEAN;
            Assert::IsTrue(actualCost == expectedCost);
        }

        /****************
        * Test Utility *
        ****************/
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
}