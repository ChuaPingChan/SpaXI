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

        TEST_METHOD(TestGetAllSynonyms_success) {
            ClauseResult cr = ClauseResult();

            string syn1 = "a";
            list<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            list<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            list<int> syn3Results{ 7 };

            cr.addNewSynResults(syn1, syn1Results);
            cr.addNewSynResults(syn2, syn2Results);
            cr.addNewSynResults(syn3, syn3Results);

            list<string> allSynonyms = cr.getAllSynonyms();
            list<string> expectedSynonyms{ syn1, syn2, syn3 };
            allSynonyms.sort();
            expectedSynonyms.sort();

            Assert::IsTrue(allSynonyms == expectedSynonyms);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult1_success) {
            ClauseResult cr = ClauseResult();

            string stmt1 = "a";
            list<int> stmt1Results{ 1, 2, 3 };

            string stmt2 = "b";
            list<int> stmt2Results{ 4, 5 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            list<list<int>> result = cr.getAllResults();

            list<list<int>> expectedResults{ {1,4}, {1,5}, {2,4}, {2,5}, {3,4}, {3,5} };

            Assert::IsTrue(result == expectedResults);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult2_success) {
            ClauseResult cr = ClauseResult();

            string stmt1 = "a";
            list<int> stmt1Results{ 1, 2, 3 };

            string stmt2 = "b";
            list<int> stmt2Results{ 6 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            list<list<int>> result = cr.getAllResults();

            list<list<int>> expectedResults{ {1,6}, {2,6}, {3,6} };

            Assert::IsTrue(result == expectedResults);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult3_success) {
            ClauseResult cr = ClauseResult();

            string stmt1 = "a";
            list<int> stmt1Results{ 6 };

            string stmt2 = "b";
            list<int> stmt2Results{ 1, 2, 3 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            list<list<int>> result = cr.getAllResults();

            list<list<int>> expectedResults{ { 6,1 },{ 6,2 },{ 6,3 } };

            Assert::IsTrue(result == expectedResults);
        }

        /**************************
         * Private Helper Methods *
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
    };
}