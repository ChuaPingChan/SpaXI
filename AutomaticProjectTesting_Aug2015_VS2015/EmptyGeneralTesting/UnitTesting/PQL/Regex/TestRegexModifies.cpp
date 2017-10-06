#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexModifies)
    {
    public:
        TEST_METHOD(TestRegex_Modifies_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Modifies(s,v)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Arg_MultipleLetters_Valid)
        {
            string str = "Modifies(validStmtRef,validEntRef)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Arg_Alphanumeric_Valid)
        {
            string str = "Modifies(va1idStmt3ef,va1id3ntRef)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Arg_IdentWithHash_Valid)
        {
            string str = "Modifies(validIdent, withHash)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Whitespaces_Valid)
        {
            string str = "Modifies  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_FirstArg_Integer_Valid)
        {
            string str = "Modifies(1,singleDigit)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
            str = "Modifies(11,multipleDigits)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        //TODO: Change to IsTrue when implement procedure
        TEST_METHOD(TestRegex_Modifies_Ident_Valid)
        {
            string str = "Modifies(\"procedure\",\"x\")";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Underscore_Valid)
        {
            string str = "Modifies(_,_)";
            Assert::IsTrue(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_ArgTwo_Int_Invalid)
        {
            string str = "Modifiess(1,2)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Underscore_Extended_Invalid)
        {
            string str = "Modifies(__,__)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_LowercaseKeyword_Invalid)
        {
            string str = "modifies(lowercase,relationshipName)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_MisspeltKeyword_Invalid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_IdentBeginsWithNumber_Invalid)
        {
            string str = "Modifies(1,\"1InvalidFirstArg\")";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
            str = "Modifies(\"2InvalidSecondArg\",2)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_ArgBeginWithIllegalChar_Invalid)
        {
            string str = "Modifies(#,#)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Brackets_Invalid)
        {
            string str = "Modifies[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
            str = "Modifies((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_SeparationBtwnArg_Invalid)
        {
            string str = "Modifies(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
            str = "Modifies(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_ArgCount_Extra_Invalid)
        {
            string str = "Modifies(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_ArgCount_Insufficient_Invalid)
        {
            string str = "Modifies(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
            str = "Modifies()";
            Assert::IsFalse(RegexValidators::isValidModifiesRegex(str));
        }
    };
}
