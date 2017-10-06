#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexParent)
    {
    public:
        TEST_METHOD(TestRegex_Parent_Integer_Valid)
        {
            string str = "Parent(1,2)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Parent(s,k)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_MultipleLetters_Valid)
        {
            string str = "Parent(validStmtRef,validStmtRef)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_Alphanumeric_Valid)
        {
            string str = "Parent(va1idStmt3ef,va1idStmtR3f)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Arg_IdentWithHash_Valid)
        {
            string str = "Parent(validIdent,withHash)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Whitespaces_Valid)
        {
            string str = "Parent  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Underscore_Valid)
        {
            string str = "Parent(_,_)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Star_Valid)
        {
            string str = "Parent*(s1,s2)";
            Assert::IsTrue(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_LowercaseKeyword_inValid)
        {
            string str = "parent(lowercase,relationshipName)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_MisspeltKeyword_inValid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Ident_BothArgs_Invalid)
        {
            string str = "Parent(\"procedure\",\"x\")";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Ident_FirstArg_Invalid)
        {
            string str = "Parent(\"procedure\",2)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Ident_SecondArg_Invalid)
        {
            string str = "Parent(1,\"x\")";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Brackets_inValid)
        {
            string str = "Parent[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
            str = "Parent((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_SeparationBtwnArg_inValid)
        {
            string str = "Parent(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
            str = "Parent(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_ArgCount_inValid)
        {
            string str = "Parent(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
            str = "Parent(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }

        TEST_METHOD(TestRegex_Parent_Star_inValid)
        {
            string str = "Parent  *  (s1, s2)";
            Assert::IsFalse(RegexValidators::isValidParentRegex(str));
        }
    };
}
