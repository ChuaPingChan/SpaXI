#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexFollows)
    {
    public:
        TEST_METHOD(TestRegex_Follows_Integer_Valid)
        {
            string str = "Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_SingleLetterSynonym_Valid)
        {
            string str = "Follows(s,k)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_MultipleLetters_Valid)
        {
            string str = "Follows(validStmtRef,validStmtRef)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_Alphanumeric_Valid)
        {
            string str = "Follows(va1idStmt3ef,va1idStmtR3f)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Arg_IdentWithHashSymbol_Valid)
        {
            string str = "Follows(validSynonym,withHashSign)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Whitespaces_Valid)
        {
            string str = "Follows  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Underscore_Valid)
        {
            string str = "Follows(_,_)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Star_Valid)
        {
            string str = "Follows*(s1,s2)";
            Assert::IsTrue(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_LowercaseKeyword_inValid)
        {
            string str = "follows(lowercase,relationshipName)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_MissingLetterS_inValid)
        {
            string str = "Follow(no,s)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_MisspeltKeyword_inValid)
        {
            string str = "misspelt(relationship,name)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Ident_BothArg_Invalid)
        {
            string str = "Follows(\"procedure\",\"x\")";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Ident_FirstArg_Invalid)
        {
            string str = "Follows(\"procedure\",2)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Ident_SecondArg_Invalid)
        {
            string str = "Follows(1,\"x\")";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Brackets_inValid)
        {
            string str = "Follows[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
            str = "Follows((validArgsSyntax, ExtraBrackets))";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_SeparationBtwnArg_inValid)
        {
            string str = "Follows(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
            str = "Follows(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_ArgCount_inValid)
        {
            string str = "Follows(validArgsSyntax, with, extraArgs)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
            str = "Follows(insufficientArgs)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }

        TEST_METHOD(TestRegex_Follows_Star_inValid)
        {
            string str = "Follows  *  (s1, s2)";
            Assert::IsFalse(RegexValidators::isValidFollowsRegex(str));
        }
    };
}
