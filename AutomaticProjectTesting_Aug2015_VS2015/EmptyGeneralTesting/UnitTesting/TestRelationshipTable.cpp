#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\Selection\RelationshipTable\RelationshipTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRelationshipTable)
    {
        RelationshipTable rt = RelationshipTable();

        TEST_METHOD(TestGetModifies)
        { 
            Assert::IsTrue(rt.isArgValid(0,0,7));
            Assert::IsFalse(rt.isArgValid(0, 0, 13));

        }
    };

}