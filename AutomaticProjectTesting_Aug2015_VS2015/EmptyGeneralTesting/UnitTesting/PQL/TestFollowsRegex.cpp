#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestFollowsRegex)
    {
    public:
        TEST_METHOD(TestRegex_Follows_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,2)";
        }

        TEST_METHOD(TestRegex_Follows_Arg_SingleLetterSynonym_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,k)";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_MultipleLetters_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(validStmtRef,validStmtRef)";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_Alphanumeric_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(va1idStmt3ef,va1idStmtR3f)";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Whitespaces_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,_)";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Star_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s1,s2)";
            Assert::IsTrue(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_LowercaseKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "follows(lowercase,relationshipName)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_MisspeltKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Ident_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(\"procedure\",\"x\")";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
            str = "Follows(\"procedure\",2)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
            str = "Follows(1,\"x\")";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Brackets_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
            str = "Follows((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_SeparationBtwnArg_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
            str = "Follows(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_ArgCount_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
            str = "Follows(insufficientArgs)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Star_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows  *  (s1, s2)";
            Assert::IsFalse(qvf.isValidFollowsRegex(str));
        }
    };
}
