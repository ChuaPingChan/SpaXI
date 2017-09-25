#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestPatternRegex)
    {
    public:

        /********************
        * Factor Regex Test *
        ********************/

        TEST_METHOD(TestRegex_Factor_VarName_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "validName";
            Assert::IsTrue(qvf.isValidFactor(str));
            str = "validName22011209040009142005070518";
            Assert::IsTrue(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_Factor_ConstValue_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "22011209040009142005070518";
            Assert::IsTrue(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_Factor_VarName_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "#invalidNameInvalidInteger";
            Assert::IsFalse(qvf.isValidFactor(str));
            str = "123invalidNameInvalidInteger";
            Assert::IsFalse(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_Factor_Idente_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "\"invalid\"";
            Assert::IsFalse(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_Factor_symbols_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "(varname)";
            Assert::IsFalse(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_Factor_Whitespaces_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = " valid   varname  ";
            Assert::IsFalse(qvf.isValidFactor(str));
        }



        /*****************************
        * Expression Spec Regex Test *
        *****************************/

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
            str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
            str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestRegex_ExpressionSpec_ExactMatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "\"exactMatch\"";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        //TODO: Change to IsTrue when implement + nad * and -
        TEST_METHOD(TestRegex_ExpressionSpec_Operator_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "\"x+y-3*z\"";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Division_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "\"x/y\"";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_EmptyString_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Integer_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "123";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Letters_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "abc";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_OnesidedUnderscore_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "_\"validFactorWithLeftSideUnderscoreOnly\"";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
            str = "\"validFactorWithRightSideUnderscoreOnly\"_";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }



        /*********************
        * Pattern Regex Test *
        *********************/

        TEST_METHOD(TestRegex_Pattern_Whitespace_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a (   validBothArgs  ,   _  )";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, _)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SecondArg_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _\"y\"_)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Uppercase_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "Pattern a(uppercase, _\"relationshipName\"_)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MisspeltKeyword_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "misspelt(relationship, _\"name\"_)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_IntegerArg_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern 1(2, 3)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }
        
        TEST_METHOD(TestRegex_Pattern_ArgCount_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern (noSynonymBeforeBracket, _)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(onlyTwoArg)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern (onlyOneArg)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a()";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(too, many, arguments)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Bracket_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a[validArgsSyntax, _\"wrongBrackets\"_]";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a((validArgsSyntax, _\"extraBrackets\"_))";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a validArgsSyntax, _\"noBrackets\"_";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SeparationBtwnArg_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }
        
    };
}
