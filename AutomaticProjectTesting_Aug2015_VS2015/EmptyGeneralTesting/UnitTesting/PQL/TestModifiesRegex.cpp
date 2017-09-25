#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestModifiesRegex)
    {
    public:
        TEST_METHOD(TestRegex_Modifies_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifiess(1,2)";
        }

        TEST_METHOD(TestRegex_Modifies_Arg_SingleLetterSynonym_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(s,v)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Arg_MultipleLetters_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(validStmtRef,validEntRef)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Arg_Alphanumeric_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(va1idStmt3ef,va1id3ntRef)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Whitespaces_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_FirstArg_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(1,singleDigit)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
            str = "Modifies(11,multipleDigits)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        //TODO: Change to IsTrue when implement procedure
        TEST_METHOD(TestRegex_Modifies_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(\"procedure\",\"x\")";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(_,_)";
            Assert::IsTrue(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_LowercaseKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "modifies(lowercase,relationshipName)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_MisspeltKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Synonym_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(1,\"1invalidFirstArg\")";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
            str = "Modifies(\"2invalidSecondArg\",2)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
            str = "Modifies(#,#)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_Brackets_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
            str = "Modifies((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_SeparationBtwnArg_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
            str = "Modifies(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }

        TEST_METHOD(TestRegex_Modifies_ArgCount_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
            str = "Modifies(insufficientArgs)";
            Assert::IsFalse(qvf.isValidModifiesRegex(str));
        }
    };
}
