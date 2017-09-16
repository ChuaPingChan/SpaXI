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
            
            Assert::IsTrue(vit.addToVarIdxTable("a", 1));
            Assert::IsTrue(vit.addToVarIdxTable("b", 2));
            Assert::IsTrue(vit.addToVarIdxTable("hello", 3));
            Assert::IsTrue(vit.addToVarIdxTable("japan", 4));
            Assert::IsTrue(vit.addToVarIdxTable("daisuki", 5));

            Assert::IsTrue(vit.getIdxFromVar("japan") == 4);
            Assert::IsFalse(vit.getIdxFromVar("lalala") == 1);

            Assert::IsTrue(vit.isVarPresent("daisuki"));
            Assert::IsFalse(vit.isVarPresent("yamete"));
        }

    };
}