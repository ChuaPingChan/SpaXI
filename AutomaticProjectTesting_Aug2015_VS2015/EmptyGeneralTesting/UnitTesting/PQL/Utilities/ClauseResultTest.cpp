#include "CppUnitTest.h"

#include "../SPA/PQL/Utilities/ClauseResultChildForTest.h"
#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseResult)
    {
    public:
        TEST_METHOD(TestAppendToVector)
        {
            std::vector<int> v = std::vector<int>();
            v.push_back(10);
            v.push_back(20);
            v.push_back(30);
            Assert::IsTrue(v.size() == 3);

            //ClauseResultChildForTest cr = ClauseResultChildForTest();
            std::vector<int> v2 = v;
            ClauseResultChildForTest::appendToVector(v, v2, 2);
            Assert::IsTrue(v.size() == 9);
            Assert::IsTrue(v[0] == 10);
            Assert::IsTrue(v[1] == 20);
            Assert::IsTrue(v[2] == 30);
            Assert::IsTrue(v[3] == 10);
            Assert::IsTrue(v[4] == 20);
            Assert::IsTrue(v[5] == 30);
            Assert::IsTrue(v[6] == 10);
            Assert::IsTrue(v[7] == 20);
            Assert::IsTrue(v[8] == 30);

        }
    };
}