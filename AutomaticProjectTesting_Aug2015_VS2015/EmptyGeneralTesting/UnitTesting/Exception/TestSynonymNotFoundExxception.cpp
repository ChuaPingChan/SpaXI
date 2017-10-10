#include "CppUnitTest.h"
#include <string>
#include "..\SPA\Exceptions\SynonymNotFoundException.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestSynonymNotFoundException)
    {
    public:
        TEST_METHOD(TestSynonymNotFoundException_DefaultMsg_Valid)
        {
            string str = "!@#$%&*InvalidSynonym";
            bool isExceptionThrown = false;
            string exceptionMsg = "";
            try {
                ThrowSynonymNotFoundException();
            }
            catch (SynonymNotFoundException& snfe) {
                isExceptionThrown = true;
                exceptionMsg = snfe.what();
            }
            Assert::IsTrue(isExceptionThrown);
            Assert::IsTrue("Synonym not found." == exceptionMsg);
        }

        TEST_METHOD(TestSynonymNotFoundException_CustomizedMsg_Valid)
        {
            string str = "!@#$%&*InvalidSynonym";
            bool isExceptionThrown = false;
            string exceptionMsg = "";
            try {
                ThrowSynonymNotFoundException(str);
            }
            catch (SynonymNotFoundException& snfe) {
                isExceptionThrown = true;
                exceptionMsg = snfe.what();
            }
            Assert::IsTrue(isExceptionThrown);
            Assert::IsTrue("Synonym not found.\nError!" == exceptionMsg);
        }

        int ThrowSynonymNotFoundException()
        {
            throw SynonymNotFoundException();
        }

        int ThrowSynonymNotFoundException(string str)
        {
            throw SynonymNotFoundException("Error!");
        }
    };
}
