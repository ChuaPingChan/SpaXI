#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexSelect)
    {
    public:

        TEST_METHOD(TestRegex_Select_SingleSynonym_Valid)
        {
            string str = "Select s";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }
    };
}