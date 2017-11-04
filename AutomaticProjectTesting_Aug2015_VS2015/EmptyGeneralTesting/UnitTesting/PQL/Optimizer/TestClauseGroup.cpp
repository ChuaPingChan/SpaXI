#include "CppUnitTest.h"
#include <string>
#include <list>

#include "../SPA/PQL/Optimizer/ClauseGroup.h"
#include "../SPA/PQL/Optimizer/ClauseCostCalculator.h"
#include "../SPA/PQL/Utilities/SelectClause.h"
#include "../SPA/PQL/Utilities/SuchThatClause.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseGroup)
    {
    public:

        TEST_METHOD(TestComputeCost) {

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
            
            vector<ClausePtr> rawClauseGroup;
            rawClauseGroup.push_back(select_a1.getSharedPtr());
            rawClauseGroup.push_back(uses_a1_v1.getSharedPtr());
            rawClauseGroup.push_back(modifies_w1_v1.getSharedPtr());
            rawClauseGroup.push_back(uses_a2_v2.getSharedPtr());
            rawClauseGroup.push_back(uses_10_ident.getSharedPtr());

            /***********
             * Testing *
             ***********/
            ClauseGroup clauseGroup(rawClauseGroup);
            int actualCost = clauseGroup.getCost();
            int expectedCost = ClauseCost::SELECT_1ARG + ClauseCost::USES_2ARGS + ClauseCost::MODIFIES_2ARGS
                + ClauseCost::USES_2ARGS + ClauseCost::USES_BOOLEAN;
            Assert::IsTrue(actualCost == expectedCost);            
        }

        TEST_METHOD(TestCompareCost) {

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
            Assert::IsTrue(ClauseGroup::compareClauseCost(select_a1.getSharedPtr(), uses_a1_v1.getSharedPtr()));
            Assert::IsFalse(ClauseGroup::compareClauseCost(uses_a1_v1.getSharedPtr(), modifies_w1_v1.getSharedPtr()));
            Assert::IsTrue(ClauseGroup::compareClauseCost(uses_10_ident.getSharedPtr(), select_a1.getSharedPtr()));
        }

        TEST_METHOD(TestSortClauses) {

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

            vector<ClausePtr> rawClauseGroup;
            rawClauseGroup.push_back(select_a1.getSharedPtr());
            rawClauseGroup.push_back(uses_a1_v1.getSharedPtr());
            rawClauseGroup.push_back(modifies_w1_v1.getSharedPtr());
            rawClauseGroup.push_back(uses_a2_v2.getSharedPtr());
            rawClauseGroup.push_back(uses_10_ident.getSharedPtr());

            /***********
             * Testing *
             ***********/
            ClauseGroup clauseGroup(rawClauseGroup);
            clauseGroup.sortClauses();
            vector<ClausePtr> sortedClauseGroup = clauseGroup.getClauseGroup();

            Assert::IsTrue(sortedClauseGroup[0]->getClauseType() == Clause::ClauseType::SUCH_THAT);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[0])->getRel() == Relationship::USES);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[0])->getArgOne() == "10");
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[0])->getArgTwo() == "dummyVar");

            Assert::IsTrue(sortedClauseGroup[1]->getClauseType() == Clause::ClauseType::SELECT);
            Assert::IsTrue(dynamic_pointer_cast<SelectClause>(sortedClauseGroup[1])->getSelectionType() == SelectionType::SELECT_SINGLE);
            Assert::IsTrue(dynamic_pointer_cast<SelectClause>(sortedClauseGroup[1])->getSingleArg() == "a1");

            Assert::IsTrue(sortedClauseGroup[2]->getClauseType() == Clause::ClauseType::SUCH_THAT);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[2])->getRel() == Relationship::MODIFIES);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[2])->getArgOne() == "w1");
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(sortedClauseGroup[2])->getArgTwo() == "v1");
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