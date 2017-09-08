#include <string>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestParser)
    {
    public:

        TEST_METHOD(testMainForUnitTest)
        {
            Parser parser;
        }

        TEST_METHOD(testDefaultConstructor) {
            Parser parser;
        }

    };
}