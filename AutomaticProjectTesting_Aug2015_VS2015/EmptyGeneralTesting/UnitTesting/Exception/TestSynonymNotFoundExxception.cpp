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

        TEST_METHOD(TestSynonymNotFoundException_Valid)
        {
            string str = "!@#$%&*InvalidSynonym";
            bool isExceptionThrown = false;
            string exceptionMsg = "";
            try {
                getIntBoolSynonym(str);
            }
            catch (SynonymNotFoundException& snfe) {
                isExceptionThrown = true;
                exceptionMsg = snfe.what();
            }
            Assert::IsTrue(isExceptionThrown);
            Assert::IsTrue("Synonym not found.\nHello" == exceptionMsg);
        }

        int getIntBoolSynonym(string str)
        {
            if (RegexValidators::isValidSynonymRegex(str))
            {
                return 1;
            }
            else
            {
                throw SynonymNotFoundException("Hello");
            }
        }
    };
}
