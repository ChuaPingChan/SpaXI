#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexCalls)
    {
    public:
        TEST_METHOD(TestRegex_Calls_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Calls(p,q)";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Arg_MultipleLetters_Valid)
        {
            string str = "Calls(proc1,proc2)";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Arg_Alphanumeric_Valid)
        {
            string str = "Calls(validProc123,validProc#)";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Whitespaces_Valid)
        {
            string str = "Calls  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }


        TEST_METHOD(TestRegex_Calls_Ident_Valid)
        {
            string str = "Calls(\"procedure1\",\"procedure2\")";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Underscore_Valid)
        {
            string str = "Calls(_,_)";
            Assert::IsTrue(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_ArgTwo_Int_Invalid)
        {
            string str = "Callss(1,2)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Underscore_Extended_Invalid)
        {
            string str = "Calls(__,__)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_MisspeltKeyword_Invalid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_IdentBeginsWithNumber_Invalid)
        {
            string str = "Calls(1,\"1InvalidFirstArg\")";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
            str = "Calls(\"2InvalidSecondArg\",2)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_ArgBeginWithIllegalChar_Invalid)
        {
            string str = "Calls(#,#)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_Brackets_Invalid)
        {
            string str = "Calls[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
            str = "Calls((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_SeparationBtwnArg_Invalid)
        {
            string str = "Calls(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
            str = "Calls(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_ArgCount_Extra_Invalid)
        {
            string str = "Calls(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }

        TEST_METHOD(TestRegex_Calls_ArgCount_Insufficient_Invalid)
        {
            string str = "Calls(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
            str = "Calls()";
            Assert::IsFalse(RegexValidators::isValidCallsRegex(str));
        }
    };
}
