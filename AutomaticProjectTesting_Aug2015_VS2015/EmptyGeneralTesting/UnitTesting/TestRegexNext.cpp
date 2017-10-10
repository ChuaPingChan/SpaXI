#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexNext)
    {
    public:
        TEST_METHOD(TestRegex_Next_Integer_Valid)
        {
            string str = "Next(1,2)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Next(s,k)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Arg_MultipleLetters_Valid)
        {
            string str = "Next(validLineRef,validLineRef)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Arg_Alphanumeric_Valid)
        {
            string str = "Next(va1idLine3ef,va1idLineR3f)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Arg_IdentWithHashSymbol_Valid)
        {
            string str = "Next(validSynonym,withHashSign)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Whitespaces_Valid)
        {
            string str = "Next  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Underscore_Valid)
        {
            string str = "Next(_,_)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Star_Valid)
        {
            string str = "Next*(s1,s2)";
            Assert::IsTrue(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_MissingLetterS_inValid)
        {
            string str = "Nex(no,s)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_MisspeltKeyword_inValid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Ident_BothArg_Invalid)
        {
            string str = "Next(\"procedure\",\"x\")";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Ident_FirstArg_Invalid)
        {
            string str = "Next(\"procedure\",2)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
            str = "Next(1,\"x\")";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Ident_SecondArg_Invalid)
        {
            string str = "Next(1,\"x\")";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Brackets_inValid)
        {
            string str = "Next[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
            str = "Next((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_SeparationBtwnArg_inValid)
        {
            string str = "Next(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
            str = "Next(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_ArgCount_inValid)
        {
            string str = "Next(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
            str = "Next(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }

        TEST_METHOD(TestRegex_Next_Star_inValid)
        {
            string str = "Next  *  (s1, s2)";
            Assert::IsFalse(RegexValidators::isValidNextRegex(str));
        }
    };
}
