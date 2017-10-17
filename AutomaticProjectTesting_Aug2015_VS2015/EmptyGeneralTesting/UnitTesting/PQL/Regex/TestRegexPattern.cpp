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

        /*************************************
        * Expression Spec Partial Regex Test *
        *************************************/
        TEST_METHOD(TestRegex_ExpressionSpecPartial_Letter_Valid)
        {
            string str = "_\"Hello\"_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Integer_Valid)
        {
            string str = "_\"12345\"_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Plus_Invalid)
        {
            string str = "_\"+\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Minus_Invalid)
        {
            string str = "_\"-\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Times_Invalid)
        {
            string str = "_\"*\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_OpenBrackets_invalid)
        {
            string str = "_\"(\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_CloseBrackets_Invalid)
        {
            string str = "_\")\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Expression_Valid)
        {
            string str = "_\"x-2*(a+b)\"_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Expression_IllegalSynonym_Invalid)
        {
            string str = "_\"2x-(2*(a-)+b)\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Whitespace_Valid)
        {
            string str = "_ \" x - 2 * ( a + b ) \" _";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecPartial_Letter_NoUnderscoreQuotes_Invalid)
        {
            string str = "Hello";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecPartialRegex(str));
        }

        /***********************************
        * Expression Spec Exact Regex Test *
        ***********************************/
        TEST_METHOD(TestRegex_ExpressionSpecExact_Letter_Valid)
        {
            string str = "\"Hello\"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Integer_Valid)
        {
            string str = "\"12345\"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Plus_Invalid)
        {
            string str = "\"+\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Minus_Invalid)
        {
            string str = "\"-\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Times_Invalid)
        {
            string str = "\"*\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_OpenBrackets_Invalid)
        {
            string str = "\"(\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_CloseBrackets_Invalid)
        {
            string str = "\")\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Expression_Valid)
        {
            string str = "\"x-2*(a+b)\"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Expression_Random_Valid)
        {
            string str = "\"2x-(2*(a-)+b)\"";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Whitespace_Valid)
        {
            string str = " \" x - 2 * ( a + b ) \"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecExactRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpecExact_Letter_UnderscoreQuotes_Inalid)
        {
            string str = "_\"Hello\"_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecExactRegex(str));
        }


        /*****************************
        * Expression Spec Regex Test *
        *****************************/
        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_NotSupposedToBeHere_Invalid)
        {
            string str = "_";
            Assert::IsFalse(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Ident_PartialMatch_Valid)
        {
            string str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_ExactMatch_Valid)
        {
            string str = "\"exactMatch\"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Operator_Valid)
        {
            string str = "\"x+y-3*z\"";
            Assert::IsTrue(RegexValidators::isValidExpressionSpecRegex(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Whitespaces_Valid)
        {
            string str = "  _   \"    whitespaces     \"   _  ";
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


        /****************************
        * Pattern Assign Regex Test *
        ****************************/
        TEST_METHOD(TestRegex_Pattern_Assign_Underscore_Valid)
        {
            string str = "a(v,_)";
            Assert::IsTrue(RegexValidators::isValidPatternAssignRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Assign_ExpressionSpec_PartialMatch_Valid)
        {
            string str = "a(v,_\"x\"_)";
            Assert::IsTrue(RegexValidators::isValidPatternAssignRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Assign_FirstArg_IdentWQ_Whitespace_Valid)
        {
            string str = " a   (  \"    x   \"   ,   _   )";
            Assert::IsTrue(RegexValidators::isValidPatternAssignRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Assign_SecondArg_Whitespace_Valid)
        {
            string str = "   a   (   v    ,   _\"x\"_    )   ";
            Assert::IsTrue(RegexValidators::isValidPatternAssignRegex(str));
        }
        

        /***************************
        * Pattern While Regex Test *
        ***************************/
        TEST_METHOD(TestRegex_Pattern_While_Synonym_Underscore_Valid)
        {
            string str = "w(v,_)";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_Synonym_Underscore_Whitespaces_Valid)
        {
            string str = "  w   (   v   ,   _   )   ";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_Underscore_Underscore_Valid)
        {
            string str = "w(_,_)";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_Underscore_Underscore_whitespaces_Valid)
        {
            string str = "   w  (      _     ,    _  )  ";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_IdentWithQuotes_Underscore_Valid)
        {
            string str = "w(\"ident\",_)";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_IdentWithQuotes_Underscore_Whitespaces_Valid)
        {
            string str = " w  (   \"   ident   \"   ,   _   )";
            Assert::IsTrue(RegexValidators::isValidPatternWhileRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_While_SecondArg_Synonym_Invalid)
        {
            string str = "w(v,v1)";
            Assert::IsFalse(RegexValidators::isValidPatternWhileRegex(str));
        }


        /************************
        * Pattern If Regex Test *
        ************************/
        TEST_METHOD(TestRegex_Pattern_If_Synonym_Underscore_Underscore_Valid)
        {
            string str = "f(v,_,_)";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_If_Synonym_Underscore_Underscore_Whitespaces_Valid)
        {
            string str = "  f   (   v    ,      _   ,      _     )    ";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_If_Underscore_Underscore_Underscore_Valid)
        {
            string str = "f(_,_,_)";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_If_Underscore_Underscore_Underscore_Whitespace_Valid)
        {
            string str = "  f   (     _      ,      _      ,     _     )    ";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_If_IdentWithQuotes_Underscore_Underscore_Valid)
        {
            string str = "f(\"procedure\",_,_)";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_If_IdentWithQuotes_Underscore_Underscore_Whitespace_Valid)
        {
            string str = "  f  (  \"     procedure    \"  ,  _   ,   _  )";
            Assert::IsTrue(RegexValidators::isValidPatternIfRegex(str));
        }



        /**************************
        * Pattern Cond Regex Test *
        **************************/
        TEST_METHOD(TestRegex_Pattern_SingleClause_Assign_Valid)
        {
            string str = "a(v,_)";
            Assert::IsTrue(RegexValidators::isValidPatternCondRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SingleClause_While_Whitespace_Valid)
        {
            string str = "  w   (   v   ,   _   )   ";
            Assert::IsTrue(RegexValidators::isValidPatternCondRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MultipleClauses_And_Valid)
        {
            string str = "a(v,_) and w(v,_)";
            Assert::IsTrue(RegexValidators::isValidPatternCondRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MultipleClauses_And_Whitespace_Valid)
        {
            string str = "  a    (   v   ,    _   )      and     w    (   v   ,   _    )      ";
            Assert::IsTrue(RegexValidators::isValidPatternCondRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MultipleClauses_And_And_And_Valid)
        {
            string str = "a(v,_) and w(v,_) and f(_,_,_) and f(\"procedure\",_,_)";
            Assert::IsTrue(RegexValidators::isValidPatternCondRegex(str));
        }


        /*********************
        * Pattern Regex Test *
        *********************/
        TEST_METHOD(TestRegex_Pattern_Whitespace_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   _  )";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Whitespace_InExpressionSpec_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   \"   x+y   \"  )";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Tabs_InExpressionSpec_Valid)
        {
            string str = "pattern a (validBothArgs,\"	x+y		\")";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Whitespace_InExpressionSpec_PartialMatch_Valid)
        {
            string str = "pattern a (   validBothArgs  ,   _   \"  var   \"   _  )";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Underscore_Underscore_Valid)
        {
            string str = "pattern a(_, _)";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SecondArg_Ident_PartialMatch_Valid)
        {
            string str = "pattern a(v, _\"y\"_)";
            Assert::IsTrue(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_UppercaseKeywordInvalid)
        {
            string str = "Pattern a(uppercase, _\"ident\"_)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_MisspeltKeywordInvalid)
        {
            string str = "misspelt(relationship, _\"name\"_)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_IntegerArgInvalid)
        {
            string str = "pattern 1(2, 3)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }
        
        TEST_METHOD(TestRegex_Pattern_ArgCount_MissingPatternTypeSynonymInvalid)
        {
            string str = "pattern (noSynonymBeforeBracket, _)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_OneArgInvalid)
        {
            string str = "pattern a(onlyTwoArg)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_ExtraInvalid)
        {
            string str = "pattern a(too, many, arguments, already)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_ArgCount_EmptyInvalid)
        {
            string str = "pattern a()";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_BracketInvalid)
        {
            string str = "pattern a[validArgsSyntax, _\"wrongBrackets\"_]";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
            str = "pattern a((validArgsSyntax, _\"extraBrackets\"_))";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
            str = "pattern a validArgsSyntax, _\"noBrackets\"_";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_SeparationBtwnArgInvalid)
        {
            string str = "pattern a(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
            str = "pattern a(validArgsSyntax noCommas)";
            Assert::IsFalse(RegexValidators::isValidPatternClRegex(str));
        }
        
    };
}
