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
            Assert::IsTrue(ct.addConstantList(1));
            Assert::IsTrue(ct.addConstantList(2));
            Assert::IsTrue(ct.addConstantList(3));
            Assert::IsTrue(ct.addConstantList(1));
            Assert::IsTrue(ct.addConstantList(5));

            Assert::IsTrue(ct.isConstant(2));
            Assert::IsTrue(ct.isConstant(5));
            Assert::IsFalse(ct.isConstant(4));
        }

    };
}