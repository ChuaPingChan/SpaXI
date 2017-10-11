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
            ClauseResult cr = ClauseResult();
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
            ClauseResult cr = ClauseResult();

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
            ClauseResult cr = ClauseResult();

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
            ClauseResult cr = ClauseResult();

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

        /**************************
         * Helper Methods *
         **************************/
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
            std::list<int> l{ 10, 20, 30};
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