#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\Selection\RelationshipTable\RelationshipTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRelationshipTable)
    {
        RelationshipTable rt;

        TEST_METHOD(TestRelationshipTableModifies)
        { 
            Assert::IsTrue(rt.isArgValid(MODIFIES,INTEGER,VARIABLE));
            Assert::IsFalse(rt.isArgValid(MODIFIES, UNDERSCORE, UNDERSCORE));

        }

        TEST_METHOD(TestRelationshipTableUses)
        {
            Assert::IsTrue(rt.isArgValid(USES, INTEGER, VARIABLE));
            Assert::IsFalse(rt.isArgValid(USES, UNDERSCORE, UNDERSCORE));

        }

        TEST_METHOD(TestRelationshipTableFollows)
        {
            Assert::IsTrue(rt.isArgValid(FOLLOWS, INTEGER, INTEGER));
            Assert::IsTrue(rt.isArgValid(FOLLOWS, UNDERSCORE, UNDERSCORE));

        }

    };

}