#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\ResultFormatter\ResultFormatter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexResultFormatter)
    {
    public:

        /************************
        * Return false result *
        ************************/

       /* TEST_METHOD(TestRegex_InvalidDeclaration_False)
        {
            ResultFormatter rf;
            string query = "stmt s;Select BOOLEAN";
            list<string> expectedResult = { "false" };
            Assert::IsTrue(rf.handleInvalidQuery(query) == expectedResult);
        }*/

    };
}
