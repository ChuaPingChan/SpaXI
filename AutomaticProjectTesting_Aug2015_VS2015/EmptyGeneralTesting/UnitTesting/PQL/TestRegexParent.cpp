#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexParent)
    {
    public:
        TEST_METHOD(TestRegex_Parent_Integer_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,2)";
        }

        TEST_METHOD(TestRegex_Parent_Arg_SingleLetterSynonym_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,k)";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_MultipleLetters_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(validStmtRef,validStmtRef)";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_Alphanumeric_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(va1idStmt3ef,va1idStmtR3f)";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Whitespaces_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,_)";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Star_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent*(s1,s2)";
            Assert::IsTrue(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_LowercaseKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "parent(lowercase,relationshipName)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_MisspeltKeyword_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Ident_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(\"procedure\",\"x\")";
            Assert::IsFalse(qvf.isValidParentRegex(str));
            str = "Parent(\"procedure\",2)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
            str = "Parent(1,\"x\")";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Brackets_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qvf.isValidParentRegex(str));
            str = "Parent((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_SeparationBtwnArg_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
            str = "Parent(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_ArgCount_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
            str = "Parent(insufficientArgs)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Star_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent  *  (s1, s2)";
            Assert::IsFalse(qvf.isValidParentRegex(str));
        }
    };
}
