#include "CppUnitTest.h"
#include <string>

#include "ClauseResultChildForTest.h"
#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseResult)
    {
    public:

        TEST_METHOD(TestMultiMethods_success) {
            /*
            Methods tested:
            1. getAllSynonyms()
            2. synonymPresent()
            3. hasResults()
            */
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());

            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };

            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);

            Assert::IsTrue(cr.synonymPresent(syn1));
            Assert::IsTrue(cr.synonymPresent(syn2));
            Assert::IsTrue(cr.synonymPresent(syn3));
            Assert::IsFalse(cr.synonymPresent("z"));
            Assert::IsFalse(cr.synonymPresent(""));

            list<string> allSynonyms = cr.getAllSynonyms();
            list<string> expectedSynonyms{ syn1, syn2, syn3 };
            allSynonyms.sort();
            expectedSynonyms.sort();

            Assert::IsTrue(allSynonyms == expectedSynonyms);
            Assert::IsTrue(cr.hasResults());
        }

        TEST_METHOD(TestUpdateSynResults_success)
        {
            ClauseResult cr;

            string stmt1 = "a";
            list<int> stmt1Results{ 1, 2, 3 };
            string stmt2 = "b";
            list<int> stmt2Results{ 4, 5 };

            cr.updateSynResults("a", stmt1Results);
            cr.updateSynResults("b", stmt2Results);
            list<list<int>> actualResult = cr.getAllResults();
            list<list<int>> expectedResults{ {1,4}, {1,5}, {2,4}, {2,5}, {3,4}, {3,5} };

            Assert::IsTrue(actualResult == expectedResults);
        }

        TEST_METHOD(TestUpdateSynResults_longResultThenShortResult_success) {
            ClauseResult cr;

            string stmt1 = "a";
            list<int> stmt1Results{ 1, 2, 3 };

            string stmt2 = "b";
            list<int> stmt2Results{ 6 };

            cr.updateSynResults("a", stmt1Results);
            cr.updateSynResults("b", stmt2Results);
            list<list<int>> actualResult = cr.getAllResults();
            list<list<int>> expectedResults{ {1,6}, {2,6}, {3,6} };

            Assert::IsTrue(actualResult == expectedResults);
        }

        TEST_METHOD(TestUpdateSynResults_shortResultThenLongResult_success) {
            ClauseResult cr;

            string stmt1 = "a";
            list<int> stmt1Results{ 6 };
            string stmt2 = "b";
            list<int> stmt2Results{ 1, 2, 3 };

            cr.updateSynResults("a", stmt1Results);
            cr.updateSynResults("b", stmt2Results);
            list<list<int>> actualResult = cr.getAllResults();
            list<list<int>> expectedResults{ { 6,1 },{ 6,2 },{ 6,3 } };

            Assert::IsTrue(actualResult == expectedResults);
        }

        TEST_METHOD(TestUpdateSynResults_existingSyn_success)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            list<int> syn1ResultsToOverlap{ 1 };
            string syn2 = "b";
            list<int> syn2Results{ 4, 5 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn1, syn1ResultsToOverlap);
            // {2,4}, {2, 5}, {3, 4} and {3, 5} should be removed

            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{ {1, 4}, {1, 5} };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestUpdateSynResults_nonOverlappingResult_success)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            list<int> syn1ResultsToOverlap{ 9, 10 };
            string syn2 = "b";
            list<int> syn2Results{ 4, 5 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn1, syn1ResultsToOverlap);    // Result should be empty

            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{};
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
            Assert::IsFalse(cr.hasResults());
        }

        TEST_METHOD(TestAddNewSynPairResults_nonEmptyExistingResults_success)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 2 };
            string syn2 = "b";
            list<int> syn2Results{ 4, 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7, 8, 9 };
            cr.updateSynResults(syn1, syn1Results);

            cr.addNewSynPairResults(syn2, syn2Results, syn3, syn3Results);
            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{ { 1, 4, 7 }, { 1, 5, 8 }, { 1, 6, 9 },
                                             { 2, 4, 7 }, { 2, 5, 8 }, { 2, 6, 9 } };
            /*********
            a   b   c
            ---------
            1   4   7
            1   5   8
            1   6   9
            2   4   7
            2   5   8
            2   6   9
            **********/
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestAddNewSynPairResults_emptyExistingResults_success)
        {
            ClauseResult cr;

            string syn2 = "b";
            list<int> syn2Results{ 4, 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7, 8, 9 };

            cr.addNewSynPairResults(syn2, syn2Results, syn3, syn3Results);
            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{ {4, 7}, {5, 8}, {6, 9} };
            /*****
             b   c
             -----
             4   7
             5   8
             6   9
             *****/
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestPairWithOldSyn_moreThanExistingResults)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 3, 4 };
            string syn2 = "b";
            list<int> syn2Results{ 8 };
            string syn3 = "c";
            list<pair<int, int>> resultPairs;
            resultPairs.clear();
            resultPairs.push_back(pair<int, int>(1, 2));
            resultPairs.push_back(pair<int, int>(3, 4));
            resultPairs.push_back(pair<int, int>(3, 6));
            resultPairs.push_back(pair<int, int>(4, 7));
            resultPairs.push_back(pair<int, int>(5, 2));

            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.pairWithOldSyn(syn1, syn3, resultPairs);
            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{ { 1, 8, 2 },{ 3, 8, 4 },
                                             { 3, 8, 6 }, {4, 8, 7} };
            /********
            a   b   c
            ---------
            1   8   2
            3   8   4
            3   8   6
            4   8   7
            *********/
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestPairWithOldSyn_partlyOverlapExistingResults)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 3, 4 };
            string syn2 = "b";
            list<int> syn2Results{ 8 };
            string syn3 = "c";
            list<pair<int, int>> resultPairs;
            resultPairs.clear();
            resultPairs.push_back(pair<int, int>(3, 4));
            resultPairs.push_back(pair<int, int>(3, 6));

            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.pairWithOldSyn(syn1, syn3, resultPairs);
            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{ { 3, 8, 4 }, { 3, 8, 6 } };
            /********
            a   b   c
            ---------
            3   8   4
            3   8   6
            *********/
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestPairWithOldSyn_NoOverlapResultPairs)
        {
            ClauseResult cr;

            string syn1 = "a";
            list<int> syn1Results{ 1, 3, 4 };
            string syn2 = "b";
            list<int> syn2Results{ 8 };
            string syn3 = "c";
            list<pair<int, int>> resultPairs;
            resultPairs.clear();
            resultPairs.push_back(pair<int, int>(5, 2));
            resultPairs.push_back(pair<int, int>(8, 11));

            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.pairWithOldSyn(syn1, syn3, resultPairs);
            list<list<int>> actualResults = cr.getAllResults();
            list<list<int>> expectedResults{};

            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestRemoveCombinations_oneSynonymPartialRemoval_success)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);

            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            3	5	7
            3	6	7
            *********/

            cr.removeCombinations(syn2, 5);     // existing value
            cr.removeCombinations(syn2, 100);   // non-existent value
            list<list<int>> expectedResults{ {1, 6, 7}, {2, 6, 7}, {3, 6, 7} };
            list<list<int>> actualResults = cr.getAllResults();
            expectedResults.sort();
            actualResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestRemoveCombinations_oneSynonymRemoveUntilEmpty_success)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);

            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            3	5	7
            3	6	7
            *********/

            cr.removeCombinations(syn2, 5);
            cr.removeCombinations(syn2, 6);
            list<list<int>> expectedResults{};
            list<list<int>> actualResults = cr.getAllResults();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestRemoveCombinations_twoSynonymsExistingValues_success)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);

            /********
            a	b	c
            ---------
            1	5	7   // remove
            1	6	7   // remove
            2	5	7
            2	6	7   // remove
            3	5	7
            3	6	7
            *********/

            cr.removeCombinations(syn1, 1, syn3, 7);    // existing values
            cr.removeCombinations(syn1, 2, syn2, 6);    // existing values
            cr.removeCombinations(syn1, 100, syn3, 100);    // non-existent values
            list<list<int>> expectedResults{ { 2, 5, 7 }, { 3, 5, 7 }, { 3, 6, 7 } };
            list<list<int>> actualResults = cr.getAllResults();
            expectedResults.sort();
            actualResults.sort();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestRemoveCombinations_twoSynonymsRemoveUntilEmpty_success)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);

            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            3	5	7
            3	6	7
            *********/

            cr.removeCombinations(syn1, 1, syn3, 7);
            cr.removeCombinations(syn2, 5, syn3, 7);
            cr.removeCombinations(syn1, 2, syn2, 6);
            cr.removeCombinations(syn1, 3, syn2, 6);
            list<list<int>> expectedResults{};
            list<list<int>> actualResults = cr.getAllResults();
            Assert::IsTrue(actualResults == expectedResults);
        }

        TEST_METHOD(TestGetSynonymResults_success)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);
            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            3	5	7
            3	6	7
            *********/

            // Get all synonym results
            list<string> synNames{ syn1, syn2, syn3 };
            list<list<int>> actualResults = cr.getSynonymResults(synNames);
            list<list<int>> expectedResults{
                {1, 5, 7},
                {1, 6, 7},
                {2, 5, 7},
                {2, 6, 7},
                {3, 5, 7},
                {3, 6, 7}
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Get only selected synonym results
            synNames = list<string>{ syn1, syn3 };
            actualResults = cr.getSynonymResults(synNames);
            expectedResults = list<list<int>>{
                { 1, 7 },
                { 2, 7 },
                { 3, 7 }
            };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Get only single synonym result
            synNames = list<string>{ syn1 };
            actualResults = cr.getSynonymResults(synNames);
            expectedResults = list<list<int>>{ { 1 }, { 2 }, { 3 } };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            synNames = list<string>{ syn2 };
            actualResults = cr.getSynonymResults(synNames);
            expectedResults = list<list<int>>{ { 5 }, { 6 } };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            synNames = list<string>{ syn3 };
            actualResults = cr.getSynonymResults(synNames);
            expectedResults = list<list<int>>{ { 7 } };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            list<int> actualSyn1Results = cr.getSynonymResults(syn1);
            list<int> actualSyn2Results = cr.getSynonymResults(syn2);
            list<int> actualSyn3Results = cr.getSynonymResults(syn3);
            list<int> expectedSyn1Results{ 1, 2, 3 };
            list<int> expectedSyn2Results{ 5, 6 };
            list<int> expectedSyn3Results{ 7 };
            actualSyn1Results.sort();
            actualSyn2Results.sort();
            actualSyn3Results.sort();
            expectedSyn1Results.sort();
            expectedSyn2Results.sort();
            expectedSyn3Results.sort();
            Assert::IsTrue(actualSyn1Results == expectedSyn1Results);
            Assert::IsTrue(actualSyn2Results == expectedSyn2Results);
            Assert::IsTrue(actualSyn3Results == expectedSyn3Results);
        }

        TEST_METHOD(TestGetSynonymPairResults)
        {
            ClauseResult cr;
            Assert::IsFalse(cr.hasResults());
            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };
            cr.updateSynResults(syn1, syn1Results);
            cr.updateSynResults(syn2, syn2Results);
            cr.updateSynResults(syn3, syn3Results);
            /********
            a	b	c
            ---------
            1	5	7
            1	6	7
            2	5	7
            2	6	7
            3	5	7
            3	6	7
            *********/

            list<pair<int, int>> actualSynPairResults;
            list<pair<int, int>> expectedSynPairResults;
            actualSynPairResults.clear();
            expectedSynPairResults.clear();

            // No duplicates
            actualSynPairResults = cr.getSynonymPairResults(syn1, syn2);
            expectedSynPairResults = list<pair<int, int>>{
                pair<int, int>(1, 5),
                pair<int, int>(1, 6),
                pair<int, int>(2, 5),
                pair<int, int>(2, 6),
                pair<int, int>(3, 5),
                pair<int, int>(3, 6),
            };
            actualSynPairResults.sort();
            expectedSynPairResults.sort();
            Assert::IsTrue(actualSynPairResults == expectedSynPairResults);

            // With duplicates
            actualSynPairResults = cr.getSynonymPairResults(syn2, syn3);
            expectedSynPairResults = list<pair<int, int>>{
                pair<int, int>(5, 7),
                pair<int, int>(6, 7)
            };
            actualSynPairResults.sort();
            expectedSynPairResults.sort();
            Assert::IsTrue(actualSynPairResults == expectedSynPairResults);
        }

        /***********************
         * Test Helper Methods *
         ***********************/
        TEST_METHOD(TestJoinTwoVectors_intVector_success)
        {
            std::vector<int> v{ 10,20,30 };
            Assert::IsTrue(v.size() == 3);

            std::vector<int> v2 = v;
            int repeatNum = 10;
            v = ClauseResultChildForTest::joinTwoVectors(v, v2, repeatNum);
            Assert::IsTrue(v.size() == (repeatNum + 1) * v2.size());
            for (int i = 0; i < v.size(); i++) {
                if (i % 3 == 0) {
                    Assert::IsTrue(v[i] == 10);
                } else if (i % 3 == 1) {
                    Assert::IsTrue(v[i] == 20);
                } else {
                    Assert::IsTrue(v[i] == 30);
                }
            }
        }

        TEST_METHOD(TestJoinTwoVectors_defaultRepeatNum_success)
        {
            std::vector<int> v1{ 10,20,30 };
            std::vector<int> v2{ 40,50,60 };
            std::vector<int> v1_copy{ 10,20,30 };
            std::vector<int> v2_copy{ 40,50,60 };


            std::vector<int> actualCombinedVector = ClauseResultChildForTest::joinTwoVectors(v1, v2);
            std::vector<int> expectedCombinedVector{ 10, 20, 30, 40, 50, 60 };
            Assert::IsTrue(actualCombinedVector == expectedCombinedVector);

            // Method shouldn't change original vectors
            Assert::IsTrue(v1 == v1_copy);
            Assert::IsTrue(v2 == v2_copy);
        }

        TEST_METHOD(TestJoinTwoVectors_emptySecondVector_success)
        {
            std::vector<int> v1{ 10, 20, 30 };
            std::vector<int> v2;
            v2.clear();

            std::vector<int> actualCombinedVector = ClauseResultChildForTest::joinTwoVectors(v1, v2);
            std::vector<int> expectedCombinedVector{ 10, 20, 30 };
            Assert::IsTrue(actualCombinedVector == expectedCombinedVector);
        }

        TEST_METHOD(TestGetUniqueVectorElements_success)
        {
            std::vector<int> v{ 10, 10, 10, 20, 20, 30, 30 };
            std::vector<int> expectedVector{ 10, 20, 30 };
            std::vector<int> actualVector = ClauseResultChildForTest::getUniqueVectorElements(v);
            Assert::IsTrue(actualVector == expectedVector);
        }

        TEST_METHOD(TestGetUniqueVectorElements_alreadyUnique_success)
        {
            std::vector<int> v{ 10, 20, 30 };
            std::vector<int> expectedVector{ 10, 20, 30 };
            std::vector<int> actualVector = ClauseResultChildForTest::getUniqueVectorElements(v);
            Assert::IsTrue(actualVector == expectedVector);
        }

        TEST_METHOD(TestGetUniqueVectorElements_emptyVector_success)
        {
            std::vector<int> v;
            v.clear();
            std::vector<int> expectedVector;
            expectedVector.clear();
            std::vector<int> actualVector = ClauseResultChildForTest::getUniqueVectorElements(v);
            Assert::IsTrue(actualVector == expectedVector);
        }

        TEST_METHOD(TestGetUniqueListElements_success)
        {
            std::list<int> l{ 10, 10, 10, 20, 20, 30, 30 };
            std::list<int> expectedList{ 10, 20, 30 };
            std::list<int> actualList = ClauseResultChildForTest::getUniqueListElements(l);
            expectedList.sort();
            actualList.sort();
            Assert::IsTrue(actualList == expectedList);
        }

        TEST_METHOD(TestGetUniqueListElements_alreadyUnique_success)
        {
            std::list<int> l{ 10, 20, 30 };
            std::list<int> expectedList{ 10, 20, 30 };
            std::list<int> actualList = ClauseResultChildForTest::getUniqueListElements(l);
            expectedList.sort();
            actualList.sort();
            Assert::IsTrue(actualList == expectedList);
        }

        TEST_METHOD(TestGetUniqueListElements_emptyList_success)
        {
            std::list<int> l{};
            std::list<int> expectedList{};
            std::list<int> actualList = ClauseResultChildForTest::getUniqueListElements(l);
            expectedList.sort();
            actualList.sort();
            Assert::IsTrue(actualList == expectedList);
        }

        TEST_METHOD(TestConvertPairToVector_success) {
            std::pair<int, int> oriPair(10, 20);
            std::vector<int> expectedVector{ 10, 20 };
            std::vector<int> actualVector = ClauseResultChildForTest::convertPairToVector(oriPair);
            Assert::IsTrue(actualVector == expectedVector);
        }

        TEST_METHOD(TestPairUpListsResults_success)
        {
            list<int> syn1Results{ 1, 2, 3 };
            list<int> syn2Results{ 2, 3, 4 };
            list<vector<int>> actualPairedUpResults = ClauseResultChildForTest::pairUpListsResults(syn1Results, syn2Results);
            list<vector<int>> expectedPairedUpResults{ {1, 2}, {2, 3}, {3, 4} };
            actualPairedUpResults.sort();
            expectedPairedUpResults.sort();
            Assert::IsTrue(actualPairedUpResults == expectedPairedUpResults);
        }
    };
}