#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestUsesRegex)
    {
    public:
        TEST_METHOD(TestRegex_Uses_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Usess(1,2)";
        }

        TEST_METHOD(TestRegex_Uses_Arg_SingleLetterSynonym_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(s,v)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Arg_MultipleLetters_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(validStmtRef,validEntRef)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Arg_Alphanumeric_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(va1idStmt3ef,va1id3ntRef)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Whitespaces_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_FirstArg_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(1,singleDigit)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
            str = "Uses(11,multipleDigits)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        //TODO: Change to IsTrue when implement procedure
        TEST_METHOD(TestRegex_Uses_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(\"procedure\",\"x\")";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(_,_)";
            Assert::IsTrue(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_LowercaseKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "modifies(lowercase,relationshipName)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_MisspeltKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Synonym_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(1,\"1invalidFirstArg\")";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
            str = "Uses(\"2invalidSecondArg\",2)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
            str = "Uses(#,#)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_Brackets_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
            str = "Uses((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_SeparationBtwnArg_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
            str = "Uses(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }

        TEST_METHOD(TestRegex_Uses_ArgCount_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
            str = "Uses(insufficientArgs)";
            Assert::IsFalse(qvf.isValidUsesRegex(str));
        }
    };
}
