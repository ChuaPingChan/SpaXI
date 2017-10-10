#include "CppUnitTest.h"
#include <string>
#include "..\SPA\Exceptions\AttributeNotFoundException.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestExceptionAttributeNotFound)
    {
    public:
        TEST_METHOD(TestAttributeNotFoundException_DefaultMsg_Valid)
        {
            string str = "!@#$%&*InvalidSynonym";
            bool isExceptionThrown = false;
            string exceptionMsg = "";
            try {
                ThrowAttributeNotFoundException();
            }
            catch (AttributeNotFoundException& snfe) {
                isExceptionThrown = true;
                exceptionMsg = snfe.what();
            }
            Assert::IsTrue(isExceptionThrown);
            Assert::IsTrue("Attribute not found." == exceptionMsg);
        }

        TEST_METHOD(TestAttributeNotFoundException_CustomizedMsg_Valid)
        {
            string str = "!@#$%&*InvalidSynonym";
            bool isExceptionThrown = false;
            string exceptionMsg = "";
            try {
                ThrowAttributeNotFoundException(str);
            }
            catch (AttributeNotFoundException& snfe) {
                isExceptionThrown = true;
                exceptionMsg = snfe.what();
            }
            Assert::IsTrue(isExceptionThrown);
            Assert::IsTrue("Attribute not found. Error!" == exceptionMsg);
        }

        int ThrowAttributeNotFoundException()
        {
            throw AttributeNotFoundException();
        }

        int ThrowAttributeNotFoundException(string str)
        {
            throw AttributeNotFoundException("Error!");
        }
    };
}
