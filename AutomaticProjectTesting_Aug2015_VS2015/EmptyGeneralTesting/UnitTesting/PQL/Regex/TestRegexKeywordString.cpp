#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexKeywordString)
    {
    public:
        TEST_METHOD(TestRegex_Stmt_String_Valid)
        {
            string str = "stmt";
            Assert::IsTrue(RegexValidators::isValidStmtString(str));
        }

        TEST_METHOD(TestRegex_Modifies_String_Valid)
        {
            string str = "Modifies";
            Assert::IsTrue(RegexValidators::isValidModifiesString(str));
        }

        TEST_METHOD(TestRegex_ProcName_String_Valid)
        {
            string str = "procName";
            Assert::IsTrue(RegexValidators::isValidProcNameString(str));
        }
    };
}