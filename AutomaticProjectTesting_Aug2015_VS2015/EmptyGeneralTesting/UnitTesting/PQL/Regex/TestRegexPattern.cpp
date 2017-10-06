#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexPattern)
    {
    public:

        /********************
        * Factor Regex Test *
        ********************/

        TEST_METHOD(TestRegex_Factor_VarName_Alphabetic_Valid)
        {
            string str = "validName";
            Assert::IsTrue(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_VarName_Alphanumeric_Valid)
        {
            string str = "validName22011209040009142005070518";
            Assert::IsTrue(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_ConstValue_SingleDigit_Valid)
        {
            string str = "2";
            Assert::IsTrue(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_ConstValue_MultiDigits_Valid)
        {
            string str = "22011209040009142005070518";
            Assert::IsTrue(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_VarName_BeginWithIllegalCharInvalid)
        {
            string str = "#invalidNameInvalidInteger";
            Assert::IsFalse(RegexValidators::isValidFactorRegex(str));
            str = "123invalidNameInvalidInteger";
            Assert::IsFalse(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_IdentInvalid)
        {
            string str = "\"invalid\"";
            Assert::IsFalse(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_SymbolsInvalid)
        {
            string str = "(varname)";
            Assert::IsFalse(RegexValidators::isValidFactorRegex(str));
        }

        TEST_METHOD(TestRegex_Factor_WhitespacesInvalid)
        {
            string str = " valid   varname  ";
            Assert::IsFalse(RegexValidators::isValidFactorRegex(str));
        }



        /*****************************
        * Expression Spec Regex Test *
        *****************************/

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_Valid)
        {
            string str = "_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Ident_PartialMatch_Valid)
        {
            string str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestRegex_ExpressionSpec_ExactMatch_Valid)
        {
            string str = "\"exactMatch\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        //TODO: Change to IsTrue when implement + and * and -
        TEST_METHOD(TestRegex_ExpressionSpec_Operator_Valid)
        {
            string str = "\"x+y-3*z\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Whitespaces_Valid)
        {
            string str = "  _   \" whitespaces \"   _  ";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Tabs_Valid)
        {
            string str = "	_	\"	tabs	\"	_	";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_DivisionInvalid)
        {
            string str = "\"x/y\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_EmptyStringInvalid)
        {
            string str = "";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_IntegerInvalid)
        {
            string str = "123";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_LettersInvalid)
        {
            string str = "abc";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_LeftOnlyInvalid)
        {
            string str = "_\"validFactorWithLeftSideUnderscoreOnly\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_RightOnlyInvalid)
        {
            string str = "\"validFactorWithRightSideUnderscoreOnly\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_InMiddleInvalid)
        {
            string str = "\"test_test\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }



        /*********************
        * Pattern Regex Test *
        *********************/

        TEST_METHOD(TestRegex_Pattern_Whitespace_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   _  )";
            Assert::IsTrue(RegexValidators::isValidPatternRegex(str));
        }

        //TODO: Change to is true when include +
        TEST_METHOD(TestRegex_Pattern_Whitespace_InExpressionSpec_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   \"   x+y   \"  )";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        //TODO: Change to is true when include +
        TEST_METHOD(TestRegex_Pattern_Tabs_InExpressionSpec_Valid)
        {
            string str = "pattern a (validBothArgs,\"	x+y		\")";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Whitespace_InExpressionSpec_PartialMatch_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   _   \"  var   \"   _  )";
            Assert::IsTrue(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Underscore_Underscore_Valid)
        {
            string str = "pattern a(_, _)";
            Assert::IsTrue(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SecondArg_Ident_PartialMatch_Valid)
        {
            string str = "pattern a(v, _\"y\"_)";
            Assert::IsTrue(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_UppercaseKeywordInvalid)
        {
            string str = "Pattern a(uppercase, _\"ident\"_)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MisspeltKeywordInvalid)
        {
            string str = "misspelt(relationship, _\"name\"_)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_IntegerArgInvalid)
        {
            string str = "pattern 1(2, 3)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }
        
        TEST_METHOD(TestRegex_Pattern_ArgCount_MissingPatternTypeSynonymInvalid)
        {
            string str = "pattern (noSynonymBeforeBracket, _)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_OneArgInvalid)
        {
            string str = "pattern a(onlyTwoArg)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_ExtraInvalid)
        {
            string str = "pattern a(too, many, arguments, already)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_EmptyInvalid)
        {
            string str = "pattern a()";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_BracketInvalid)
        {
            string str = "pattern a[validArgsSyntax, _\"wrongBrackets\"_]";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
            str = "pattern a((validArgsSyntax, _\"extraBrackets\"_))";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
            str = "pattern a validArgsSyntax, _\"noBrackets\"_";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SeparationBtwnArgInvalid)
        {
            string str = "pattern a(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
            str = "pattern a(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidPatternRegex(str));
        }
        
    };
}
