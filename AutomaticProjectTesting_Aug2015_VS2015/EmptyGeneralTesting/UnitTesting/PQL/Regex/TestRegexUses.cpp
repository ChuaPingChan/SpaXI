#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexUses)
    {
    public:
        TEST_METHOD(TestRegex_Uses_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Uses(s,v)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Arg_MultipleLetters_Valid)
        {
            string str = "Uses(validStmtRef,validEntRef)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Arg_Alphanumeric_Valid)
        {
            string str = "Uses(va1idStmt3ef,va1id3ntRef)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Whitespaces_Valid)
        {
            string str = "Uses  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_FirstArg_Integer_Valid)
        {
            string str = "Uses(1,singleDigit)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
            str = "Uses(11,multipleDigits)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        //TODO: Change to IsTrue when implement procedure
        TEST_METHOD(TestRegex_Uses_Ident_Valid)
        {
            string str = "Uses(\"procedure\",\"x\")";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Underscore_Valid)
        {
            string str = "Uses(_,_)";
            Assert::IsTrue(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_ArgTwo_Int_Invalid)
        {
            string str = "Usess(1,2)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Underscore_Extended_Invalid)
        {
            string str = "Uses(__,__)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_LowercaseKeyword_Invalid)
        {
            string str = "modifies(lowercase,relationshipName)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_MisspeltKeyword_Invalid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Synonym_BeginsWithInt_Invalid)
        {
            string str = "Uses(1,\"1InvalidFirstArg\")";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
            str = "Uses(\"2InvalidSecondArg\",2)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Synonym_BeginsWithIllegalChar_Invalid)
        {
            string str = "Uses(#,#)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Brackets_Invalid)
        {
            string str = "Uses[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
            str = "Uses((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_SeparationBtwnArg_Invalid)
        {
            string str = "Uses(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
            str = "Uses(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_ArgCount_Extra_Invalid)
        {
            string str = "Uses(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_ArgCount_Insufficient_Invalid)
        {
            string str = "Uses(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidUsesRegex(str));
        }
    };
}
