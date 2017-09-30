#include "CppUnitTest.h"
#include <string>

#include "../SPA/PQL/Utilities/ClauseResultChildForTest.h"
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

        TEST_METHOD(TestAppendToVector_stringVector_success)
        {
            std::vector<string> v = std::vector<string>();
            v.push_back("a");
            v.push_back("b");
            v.push_back("c");
            Assert::IsTrue(v.size() == 3);

            std::vector<string> v2 = v;
            int repeatNum = 10;
            ClauseResultChildForTest::appendToVector(v, v2, repeatNum);
            Assert::IsTrue(v.size() == (repeatNum + 1) * v2.size());
            for (int i = 0; i < v.size(); i++) {
                if (i % 3 == 0) {
                    Assert::IsTrue(v[i] == "a");
                } else if (i % 3 == 1) {
                    Assert::IsTrue(v[i] == "b");
                } else {
                    Assert::IsTrue(v[i] == "c");
                }
            }
        }

        TEST_METHOD(TestAddNewSynResults_nonZeroIntResults_success) {
            Assert::IsFalse(true);
        }
    };
}