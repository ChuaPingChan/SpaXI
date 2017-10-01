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
        TEST_METHOD(TestAppendToVector_intVector_success)
        {
            std::vector<int> v = std::vector<int>();
            v.push_back(10);
            v.push_back(20);
            v.push_back(30);
            Assert::IsTrue(v.size() == 3);

            std::vector<int> v2 = v;
            int repeatNum = 10;
            ClauseResultChildForTest::appendToVector(v, v2, repeatNum);
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

        TEST_METHOD(TestGetAllSynonyms_success) {
            ClauseResult cr = ClauseResult();

            string syn1 = "a";
            vector<int> syn1Results{ 1, 2, 3 };
            string syn2 = "b";
            vector<int> syn2Results{ 5, 6 };
            string syn3 = "c";
            vector<int> syn3Results{ 7 };

            cr.addNewSynResults(syn1, syn1Results);
            cr.addNewSynResults(syn2, syn2Results);
            cr.addNewSynResults(syn3, syn3Results);

            vector<string> allSynonyms = cr.getAllSynonyms();
            vector<string> expectedSynonyms{ syn1, syn2, syn3 };
            
            Assert::IsTrue(allSynonyms == expectedSynonyms);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult1_success) {
            ClauseResult cr = ClauseResult();
            
            string stmt1 = "a";
            vector<int> stmt1Results{ 1, 2, 3 };
            
            string stmt2 = "b";
            vector<int> stmt2Results{ 4, 5 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            vector<vector<int>> result = cr.getAllResults();
            
            vector<vector<int>> expectedResults{ {1,4}, {1,5}, {2,4}, {2,5}, {3,4}, {3,5} };

            Assert::IsTrue(result == expectedResults);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult2_success) {
            ClauseResult cr = ClauseResult();

            string stmt1 = "a";
            vector<int> stmt1Results{ 1, 2, 3 };

            string stmt2 = "b";
            vector<int> stmt2Results{ 6 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            vector<vector<int>> result = cr.getAllResults();

            vector<vector<int>> expectedResults{ {1,6}, {2,6}, {3,6} };

            Assert::IsTrue(result == expectedResults);
        }

        TEST_METHOD(TestAddNewSynResults_sampleResult3_success) {
            ClauseResult cr = ClauseResult();

            string stmt1 = "a";
            vector<int> stmt1Results{ 6 };

            string stmt2 = "b";
            vector<int> stmt2Results{ 1, 2, 3 };

            cr.addNewSynResults("a", stmt1Results);
            cr.addNewSynResults("b", stmt2Results);
            vector<vector<int>> result = cr.getAllResults();

            vector<vector<int>> expectedResults{ { 6,1 },{ 6,2 },{ 6,3 } };

            Assert::IsTrue(result == expectedResults);
        }
    };
}