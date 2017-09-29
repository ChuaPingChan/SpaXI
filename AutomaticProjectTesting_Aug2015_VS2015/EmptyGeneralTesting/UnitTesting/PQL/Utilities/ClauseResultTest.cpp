#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTesting
{

    TEST_CLASS(TestClassName)
    {
    public:
        TEST_METHOD(TestMethodName)
        {
            int i = 3;
            Assert::IsFalse(i == 4);
        }
    };
}