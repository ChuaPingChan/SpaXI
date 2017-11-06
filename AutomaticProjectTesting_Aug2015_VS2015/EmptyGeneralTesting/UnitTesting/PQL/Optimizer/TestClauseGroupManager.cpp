#include "CppUnitTest.h"
#include <string>
#include <queue>

#include "../SPA/PQL/Optimizer/Optimizer.h"
#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/Utilities/Clause.h"
#include "../SPA/PQL/Utilities/SuchThatClause.h"
#include "../SPA/PQL/Utilities/PatternClause.h"
#include "../SPA/PQL/Utilities/WithClause.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseGroupManager)
    {
    public:

        TEST_METHOD(TestSetAndGetNextClauseGroup) {

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

            SelectClausePtr select_a1_ptr;
            SuchThatClausePtr uses_a1_v1_ptr;
            SuchThatClausePtr modifies_w1_v1_ptr;
            SuchThatClausePtr uses_a2_v2_ptr;
            SuchThatClausePtr uses_10_ident_ptr;
            select_a1_ptr = select_a1.getSharedPtr();
            uses_a1_v1_ptr = uses_a1_v1.getSharedPtr();
            modifies_w1_v1_ptr = modifies_w1_v1.getSharedPtr();
            uses_a2_v2_ptr = uses_a2_v2.getSharedPtr();
            uses_10_ident_ptr = uses_10_ident.getSharedPtr();

            queue<ClauseGroup> tempClauseGroupQueue;
            vector<ClausePtr> tempClausesVec;

            tempClausesVec.push_back(uses_10_ident_ptr);
            tempClauseGroupQueue.push(tempClausesVec);

            tempClausesVec = vector<ClausePtr>();
            tempClausesVec.push_back(uses_a1_v1_ptr);
            tempClausesVec.push_back(modifies_w1_v1_ptr);
            tempClauseGroupQueue.push(tempClausesVec);

            tempClausesVec = vector<ClausePtr>();
            tempClausesVec.push_back(uses_a2_v2_ptr);
            tempClauseGroupQueue.push(tempClausesVec);

            /***********
             * Testing *
             ***********/
            ClauseGroupManager clauseGroupManager;
            clauseGroupManager.setClauseGroupQueue(tempClauseGroupQueue);

            ClauseGroup nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            Assert::IsTrue(nextClauseGroup.front() == uses_10_ident_ptr);

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 2);
            Assert::IsTrue(nextClauseGroup.front() == uses_a1_v1_ptr);
            nextClauseGroup.pop();
            Assert::IsTrue(nextClauseGroup.front() == modifies_w1_v1_ptr);

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            Assert::IsTrue(nextClauseGroup.front() == uses_a2_v2_ptr);

            Assert::IsFalse(clauseGroupManager.hasNextClauseGroup());
        }

        TEST_METHOD(TestMergeAndGetMergedClauseResult) {

            /***********
             * Testing *
             ***********/
            ClauseGroupManager clauseGroupManager;
            ClauseResult expectedCr;
            ClauseResult actualCr;
            list<list<int>> expectedResults;
            list<list<int>> actualResults;

            Assert::IsTrue(expectedCr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            expectedCr.updateSynResults(syn1, syn1Results);
            expectedCr.updateSynResults(syn2, syn2Results);
            expectedCr.updateSynResults(syn3, syn3Results);
            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            *********/

            // All synonyms in clause result are selected. Merge only one clause result.
            clauseGroupManager.setSelectedSynonyms(list<string>{syn1, syn2, syn3});
            clauseGroupManager.mergeClauseResult(expectedCr);
            actualCr = clauseGroupManager.getMergedClauseResult();
            actualResults = actualCr.getAllResults();
            expectedResults = expectedCr.getAllResults();
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Only some of the synonyms in clause result are selected. Merge only one clause result.
            expectedCr = ClauseResult();
            expectedCr.updateSynResults(syn1, syn1Results);
            expectedCr.updateSynResults(syn3, syn3Results);
            /********
            a	c
            -----
            1	7
            2   7
            *********/
            clauseGroupManager = ClauseGroupManager();
            clauseGroupManager.setSelectedSynonyms(list<string>{syn1, syn3});
            clauseGroupManager.mergeClauseResult(expectedCr);
            actualCr = clauseGroupManager.getMergedClauseResult();
            actualResults = actualCr.getAllResults();
            expectedResults = expectedCr.getAllResults();
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Merge two clause results. Select all synonyms.
            expectedCr = ClauseResult();
            expectedCr.updateSynResults(syn1, syn1Results);
            expectedCr.updateSynResults(syn3, syn3Results);
            /********
            a	c
            -----
            1	7
            2   7
            *********/
            clauseGroupManager = ClauseGroupManager();
            clauseGroupManager.setSelectedSynonyms(list<string>{syn1, syn2, syn3});

            clauseGroupManager.mergeClauseResult(expectedCr);   // Merge first clause result
            
            expectedCr = ClauseResult();
            expectedCr.updateSynResults(syn2, syn2Results);
            /********
            b
            ---------
            5
            6
            *********/
            clauseGroupManager.mergeClauseResult(expectedCr);   // Merge second result

            actualCr = clauseGroupManager.getMergedClauseResult();
            actualResults = actualCr.getAllResults();
            expectedResults = list<list<int>>{ {1, 7, 5}, {1, 7, 6}, {2, 7, 5}, {2, 7, 6} };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Merge two clause results. Select only some synonyms.
            expectedCr = ClauseResult();
            expectedCr.updateSynResults(syn1, syn1Results);
            expectedCr.updateSynResults(syn3, syn3Results);
            /********
            a	c
            -----
            1	7
            2   7
            *********/
            clauseGroupManager = ClauseGroupManager();
            clauseGroupManager.setSelectedSynonyms(list<string>{syn1, syn2});

            clauseGroupManager.mergeClauseResult(expectedCr);   // Merge first clause result
            
            expectedCr = ClauseResult();
            expectedCr.updateSynResults(syn2, syn2Results);
            /********
            b
            ---------
            5
            6
            *********/
            clauseGroupManager.mergeClauseResult(expectedCr);   // Merge second result

            actualCr = clauseGroupManager.getMergedClauseResult();
            actualResults = actualCr.getAllResults();
            expectedResults = list<list<int>>{ { 1, 5 },{ 1, 6 },{ 2, 5 },{ 2, 6 } };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

        }
    };
}