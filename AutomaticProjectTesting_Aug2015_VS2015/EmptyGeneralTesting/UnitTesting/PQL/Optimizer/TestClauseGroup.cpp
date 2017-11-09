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
            pair<ClausePtr, int> clauseCostPair1;
            pair<ClausePtr, int> clauseCostPair2;

            clauseCostPair1 = pair<ClausePtr, int>(select_a1.getSharedPtr(), ClauseCostCalculator::getCost(select_a1.getSharedPtr()));
            clauseCostPair2 = pair<ClausePtr, int>(uses_a1_v1.getSharedPtr(), ClauseCostCalculator::getCost(uses_a1_v1.getSharedPtr()));
            Assert::IsTrue(ClauseGroup::compareClauseCost(clauseCostPair1, clauseCostPair2));
            clauseCostPair1 = pair<ClausePtr, int>(select_a1.getSharedPtr(), ClauseCostCalculator::getCost(select_a1.getSharedPtr()));
            clauseCostPair2 = pair<ClausePtr, int>(modifies_w1_v1.getSharedPtr(), ClauseCostCalculator::getCost(modifies_w1_v1.getSharedPtr()));
            Assert::IsTrue(ClauseGroup::compareClauseCost(clauseCostPair1, clauseCostPair2));
            clauseCostPair1 = pair<ClausePtr, int>(uses_10_ident.getSharedPtr(), ClauseCostCalculator::getCost(uses_10_ident.getSharedPtr()));
            clauseCostPair2 = pair<ClausePtr, int>(select_a1.getSharedPtr(), ClauseCostCalculator::getCost(select_a1.getSharedPtr()));
            Assert::IsTrue(ClauseGroup::compareClauseCost(clauseCostPair1, clauseCostPair2));
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

        TEST_METHOD(TestPruneClauseResult) {

            /**********
            * Set up *
            **********/
            /*
            Select <a1, w1>
            such that Modifies(a2, "c")
            such that Modifies(w1, v1)
            such that Uses(s1, v2)
            */

            SelectClause select_a1_w1 = SelectClause(SelectionType::SELECT_TUPLE, vector<Entity>{Entity::ASSIGN, Entity::WHILE}, vector<string>{"a1", "w1"});
            SuchThatClause modifies_a2_ident = SuchThatClause(Relationship::MODIFIES,
                Entity::ASSIGN, "a2",
                Entity::IDENT_WITHQUOTES, "c");
            SuchThatClause uses_w1_v1 = SuchThatClause(Relationship::MODIFIES,
                Entity::WHILE, "w1",
                Entity::VARIABLE, "v1");
            SuchThatClause uses_s1_v2 = SuchThatClause(Relationship::USES,
                Entity::STMT, "s1",
                Entity::VARIABLE, "v2");

            vector<ClausePtr> rawClauseGroup;
            rawClauseGroup.push_back(select_a1_w1.getSharedPtr());
            rawClauseGroup.push_back(modifies_a2_ident.getSharedPtr());
            rawClauseGroup.push_back(uses_w1_v1.getSharedPtr());
            rawClauseGroup.push_back(uses_s1_v2.getSharedPtr());

            ClauseResult cr1;

            string a1 = "a1";
            list<int> a1Results{ 1 };
            string a2 = "a2";
            list<int> a2Results{ 2 };
            string v1 = "v1";
            list<int> v1Results{ 3 };
            string w1 = "w1";
            list<int> w1Results{ 4 };
            string v2 = "v2";
            list<int> v2Results{ 5 };
            string s1 = "s1";
            list<int> s1Results{ 6 };

            /***********
            * Testing *
            ***********/
            list<list<int>> actualResults;
            list<list<int>> expectedResults;

            ClauseGroup clauseGroup(rawClauseGroup);
            list<string> selectedSyns = select_a1_w1.getSynonyms();
            clauseGroup.setSelectedSynonyms(unordered_set<string>{selectedSyns.begin(), selectedSyns.end()});
            
            // Evaluate Modifies(a2, "c")
            clauseGroup.getNextClause();
            cr1.updateSynResults(a2, a2Results);
            /*************
            ClauseResult:
            --------------
            a2
            --------------
            2
            **************/
            actualResults = cr1.getAllResults();    // Before pruning
            expectedResults = list<list<int>>{
                {2}
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
            clauseGroup.pruneClauseResult(&cr1);
            actualResults = cr1.getAllResults();    // Afer pruning
            expectedResults = list<list<int>>{
                { -1 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Evaluate Modifies(w1,v1)
            clauseGroup.getNextClause();
            cr1.updateSynResults(w1, w1Results);
            cr1.updateSynResults(v1, v1Results);
            /*************
            ClauseResult:
            --------------
            a2	w1  v1
            --------------
            -1  4   3
            **************/
            actualResults = cr1.getAllResults();    // Before pruning
            expectedResults = list<list<int>>{
                { -1, 4, 3 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
            clauseGroup.pruneClauseResult(&cr1);
            actualResults = cr1.getAllResults();    // After pruning
            expectedResults = list<list<int>>{
                { -1, 4, -1 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Evaluate Uses(s1,v2)
            clauseGroup.getNextClause();
            cr1.updateSynResults(s1, s1Results);
            cr1.updateSynResults(v2, v2Results);
            /*****************
            ClauseResult:
            ------------------
            a2	w1  v1  s1  v2
            ------------------
            -1  4   -1   6   5
            ******************/
            actualResults = cr1.getAllResults();    // Before pruning
            expectedResults = list<list<int>>{
                { -1, 4, -1, 6, 5 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
            clauseGroup.pruneClauseResult(&cr1);
            actualResults = cr1.getAllResults();    // After pruning
            expectedResults = list<list<int>>{
                { -1, 4, -1, -1, -1 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Evaluate Select<a1, w1>
            clauseGroup.getNextClause();
            cr1.updateSynResults(a1, a1Results);
            cr1.updateSynResults(w1, w1Results);
            /*********************
            ClauseResult:
            ----------------------
            a2	w1  v1  s1  v2  a1
            ----------------------
            -1  4   -1  -1  -1  1
            **********************/
            actualResults = cr1.getAllResults();    // Before pruning
            expectedResults = list<list<int>>{
                { -1, 4, -1, -1, -1, 1 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
            clauseGroup.pruneClauseResult(&cr1);
            actualResults = cr1.getAllResults();    // After pruning
            expectedResults = list<list<int>>{
                { -1, 4, -1, -1, -1, 1 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

    };
}
