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
            int expectedCost = 
                ClauseCostCalculator::ClauseCost::SELECT_1ARG
                + ClauseCostCalculator::ClauseCost::USES_2ARGS
                + ClauseCostCalculator::ClauseCost::MODIFIES_2ARGS
                + ClauseCostCalculator::ClauseCost::USES_2ARGS
                + ClauseCostCalculator::ClauseCost::USES_BOOLEAN;
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
            ClausePtr clausePtr;

            clausePtr = clauseGroup.getNextClause();
            Assert::IsTrue(clausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getRel() == Relationship::USES);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getArgOne() == "10");
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getArgTwo() == "dummyVar");

            clausePtr = clauseGroup.getNextClause();
            Assert::IsTrue(clausePtr->getClauseType() == Clause::ClauseType::SELECT);
            Assert::IsTrue(dynamic_pointer_cast<SelectClause>(clausePtr)->getSelectionType() == SelectionType::SELECT_SINGLE);
            Assert::IsTrue(dynamic_pointer_cast<SelectClause>(clausePtr)->getSingleArg() == "a1");

            clausePtr = clauseGroup.getNextClause();
            Assert::IsTrue(clausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getRel() == Relationship::MODIFIES);
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getArgOne() == "w1");
            Assert::IsTrue(dynamic_pointer_cast<SuchThatClause>(clausePtr)->getArgTwo() == "v1");
        }

    };
}
