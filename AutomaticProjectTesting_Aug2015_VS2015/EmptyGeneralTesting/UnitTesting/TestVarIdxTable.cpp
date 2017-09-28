#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/VarIdxTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestVarIdxTable)
    {
    public:

        TEST_METHOD(TestPopulate)
        {
            VarIdxTable vit;
            
            Assert::IsTrue(vit.addToVarIdxTable("a"));
            Assert::IsTrue(vit.addToVarIdxTable("b"));
            Assert::IsTrue(vit.addToVarIdxTable("hello"));
            Assert::IsTrue(vit.addToVarIdxTable("japan"));
            Assert::IsTrue(vit.addToVarIdxTable("daisuki"));

            Assert::IsTrue(vit.getIdxFromVar("japan") == 3);
            Assert::IsFalse(vit.getIdxFromVar("lalala") == 1);

            Assert::IsTrue(vit.isVarPresent("daisuki"));
            Assert::IsFalse(vit.isVarPresent("yamete"));

			Assert::IsTrue(vit.getIdxFromVar("A") == -1);

        }

    };
}