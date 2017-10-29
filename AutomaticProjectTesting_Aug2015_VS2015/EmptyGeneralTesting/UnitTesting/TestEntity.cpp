#include "CppUnitTest.h"
#include <string>

#include "../SPA/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestEntity)
    {
    public:

        TEST_METHOD(TestEntityIsSynonym) {
            Assert::IsTrue(entityIsSynonym(Entity::ASSIGN));
        }
    };
}