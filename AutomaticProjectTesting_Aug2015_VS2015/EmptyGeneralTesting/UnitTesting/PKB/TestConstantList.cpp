#include "../stdafx.h"
#include "CppUnitTest.h"
#include "../../SPA/PKB/ConstantTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestConstantList)
    {
    public:

        TEST_METHOD(TestPopulate)
        {
            ConstantTable ct;
            Assert::IsTrue(ct.addConstantList(1, 1));
            Assert::IsTrue(ct.addConstantList(1, 2));
            Assert::IsTrue(ct.addConstantList(1, 3));
            Assert::IsTrue(ct.addConstantList(2, 1));
            Assert::IsTrue(ct.addConstantList(3, 5));

            Assert::IsTrue(ct.hasConstants(1, 2));
            Assert::IsTrue(ct.hasConstants(3, 5));
            Assert::IsFalse(ct.hasConstants(2, 3));

            list<int> expected;
            expected.push_back(1);
            expected.push_back(2);
            expected.push_back(3);
            list<int> test = ct.getStmtConstants(1);
            while (!test.empty() && !expected.empty()) 
            {
                Assert::AreEqual(test.front(), expected.front());
                test.pop_front();
                expected.pop_front();
            }
        }

    };
}