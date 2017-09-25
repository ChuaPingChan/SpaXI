#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryValidator.h"
#include "..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestQueryValidator)
    {
    public:

        /**********************
        * Grammar Regex Tests *
        **********************/
        TEST_METHOD(TestLetterRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "a";
            Assert::IsTrue(qvf.isValidLetter(str));
        }

        TEST_METHOD(TestLetterRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "invalid";
            Assert::IsFalse(qvf.isValidLetter(str));
            str = "#";
            Assert::IsFalse(qvf.isValidLetter(str));
            str = "2";
            Assert::IsFalse(qvf.isValidLetter(str));
            str = " ";
            Assert::IsFalse(qvf.isValidLetter(str));
            str = "";
            Assert::IsFalse(qvf.isValidLetter(str));
        }

        TEST_METHOD(TestIntegerRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "1";
            Assert::IsTrue(qvf.isValidInteger(str));
            str = "0123";
            Assert::IsTrue(qvf.isValidInteger(str));
        }

        TEST_METHOD(TestIntegerRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "invalid integer";
            Assert::IsFalse(qvf.isValidInteger(str));
            str = "_";
            Assert::IsFalse(qvf.isValidInteger(str));
            str = " ";
            Assert::IsFalse(qvf.isValidInteger(str));
            str = "";
            Assert::IsFalse(qvf.isValidInteger(str));
        }

        TEST_METHOD(TestSynonymRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "a";
            Assert::IsTrue(qvf.isValidSynonym(str));
            str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qvf.isValidSynonym(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qvf.isValidSynonym(str));
            str = "nameWith#SymbolWithoutNumbers";
            Assert::IsTrue(qvf.isValidSynonym(str));
            str = "nameW1thNumb3rAnd#Symbol";
            Assert::IsTrue(qvf.isValidSynonym(str));
            str = "assign";
            Assert::IsTrue(qvf.isValidSynonym(str));
        }

        TEST_METHOD(TestSynonymRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "0";
            Assert::IsFalse(qvf.isValidSynonym(str));
            str = "#";
            Assert::IsFalse(qvf.isValidSynonym(str));
            str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qvf.isValidSynonym(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qvf.isValidSynonym(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qvf.isValidSynonym(str));
        }

        TEST_METHOD(TestStmtRefRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "validSynonym";
            Assert::IsTrue(qvf.isValidStmtRef(str));
            str = "_";
            Assert::IsTrue(qvf.isValidStmtRef(str));
            str = "22011209040009142005070518";
            Assert::IsTrue(qvf.isValidStmtRef(str));
        }

        TEST_METHOD(TestStmtRefRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "validSynonym_validUnderscore_22011209040009142005070518";
            Assert::IsFalse(qvf.isValidStmtRef(str));
            str = "\"validIdentWithQuotationMarks\"";
            Assert::IsFalse(qvf.isValidStmtRef(str));
        }

        TEST_METHOD(TestEntRefRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "validSynonym";
            Assert::IsTrue(qvf.isValidEntRef(str));
            str = "_";
            Assert::IsTrue(qvf.isValidEntRef(str));
            str = "\"validIdentWithQuotationMarks\"";
            Assert::IsTrue(qvf.isValidEntRef(str));
        }

        TEST_METHOD(TestEntRefRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "validSynonym_validUnderscore_\"validIdentW1thQu0tationMarks\"";
            Assert::IsFalse(qvf.isValidEntRef(str));
        }

        TEST_METHOD(TestNameRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "a";
            Assert::IsTrue(qvf.isValidName(str));
            str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qvf.isValidName(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qvf.isValidName(str));
            str = "assign";
            Assert::IsTrue(qvf.isValidName(str));
        }

        TEST_METHOD(TestNameRegex_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "0";
            Assert::IsFalse(qvf.isValidName(str));
            str = "#";
            Assert::IsFalse(qvf.isValidName(str));
            str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qvf.isValidName(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qvf.isValidName(str));
        }


        /******************
        * Tokenizer Tests *
        ******************/
        TEST_METHOD(TestToknenizer_Split_Equality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a;select a;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreEqual((std::string) "assign a", splitted.at(0));
            Assert::AreEqual((std::string) "select a", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_SplitWithSpaces_Equality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a     ; select a     ;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreEqual((std::string) "assign a     ", splitted.at(0));
            Assert::AreEqual((std::string) " select a     ", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_SplitWithSpaces_Inequality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a     ; select a     ;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreNotEqual((std::string) "assign a", splitted.at(0));
            Assert::AreNotEqual((std::string) " select a", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_WithNewDeclarationAtStart_Inequality)
        {
            QueryValidatorFriend qvf;
            string str = "while w;assign a;select a;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreNotEqual((std::string) "assign a", splitted.at(0));
            Assert::AreNotEqual((std::string) " select a", splitted.at(1));
        }


        /********************
        * Remove all spaces *
        ********************/
        TEST_METHOD(TestRemoveAllSpaces)
        {
            QueryValidatorFriend qvf;
            string str = " a  b    c  ";
            Assert::IsTrue(qvf.removeAllSpaces(str) == "abc");
        }


        /******************
        * Substring Tests *
        ******************/
        TEST_METHOD(TestSubstringBetween_UniqueCharDelims)
        {
            QueryValidatorFriend qvf;
            string str = "abcdefghijklmnop#$%123456789";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "g", "5") == "hijklmnop#$%1234");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "c", "7") == "hijklmnop#$%1234");
        }

        /*TEST_METHOD(TestSubstringBetweenSameCharDelims)
        {
        QueryValidatorFriend qvf;
        string str = "TestBetweenSameCharDelims";
        Assert::IsTrue(qvf.getBetweenTwoStrings(str, "e", "e") == "stBetweenSameCharD");
        Assert::IsFalse(qvf.getBetweenTwoStrings(str, "e", "e") == "stBetwe");
        }*/

        /*TEST_METHOD(TestSubstringBetweenWhiteSpaceDelims)
        {
        QueryValidatorFriend qvf;
        string str = "Test between white space delims";
        Assert::IsTrue(qvf.getBetweenTwoStrings(str, " ", " ") == "between");
        Assert::IsFalse(qvf.getBetweenTwoStrings(str, " ", " ") == "white space");
        }*/

        TEST_METHOD(TestSubstringBetweenDelims_ExtractUsesArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(a,b)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "a");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "b");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "(", ",") == "(a");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ")") == "b)");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractModifiesArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Modifes(abc,def)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "abc");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "def");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "(", ",") == "(awf");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "31") == "awfwf");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractFollowsArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,b)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "a");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "b");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ",") == "qeeq");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractFollowsStarArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(123,456)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "123");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "456");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "rwr") == "3121");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractParentArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(abc123,def)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "abc123");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "def");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "\"") == "qeeq");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractParentStarArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Parent*(1,2)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "Parent", "(") == "*");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "Parent*(", ",") == "1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "2");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "2") == ",");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractPatternArgs)
        {
            QueryValidatorFriend qvf;
            string str = "patternarg1(arg2,arg3)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "pattern", "(") == "arg1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "arg2");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "arg3");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "ern", "(") == "arg1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "arg2", "arg3") == ",");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ")") == "arg2");
        }


        /********************
        * Declaration Tests *
        ********************/
        TEST_METHOD(TestEntityRegex_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "procedure";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "stmtLst";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "stmt";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "assign";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "call";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "while";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "if";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "variable";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "constant";
            Assert::IsTrue(qvf.isValidEntity(str));
            str = "prog_line";
            Assert::IsTrue(qvf.isValidEntity(str));
        }

        TEST_METHOD(TestEntityRegex_inValid)
        {
            QueryValidatorFriend qvf;
            string str = "invalidEntity";
            Assert::IsFalse(qvf.isValidEntity(str));
            str = "invalidEntityEndsWith#";
            Assert::IsFalse(qvf.isValidEntity(str));
            str = "invalidEntityEndsWith1";
            Assert::IsFalse(qvf.isValidEntity(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qvf.isValidEntity(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qvf.isValidEntity(str));
        }

        TEST_METHOD(TestQueryDeclaration_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "assign validEntityAndSynonym";
            Assert::IsTrue(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "stmt validEntity  , separatedByComma ,      multipleValidSynonym";
            Assert::IsTrue(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "stmt validEntity, mixedCommaFormat     ,      multipleVa1idSynonym";
            Assert::IsTrue(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestQueryDeclaration_Invalid)
        {
            QueryValidatorFriend qvf;
            qvf = QueryValidatorFriend();
            string str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "invalidEntity validSynonym";
            Assert::IsFalse(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "assign validEntity, inv@lidSynonym";
            Assert::IsFalse(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(qvf.isValidDeclaration(str));
            qvf = QueryValidatorFriend();
            str = "assign validEntity, validSynonymRepeted, validSynonymRepeted";
            Assert::IsFalse(qvf.isValidDeclaration(str));
        }


        /***************
        * Select Tests *
        ***************/
        TEST_METHOD(TestSelectOverallRegex_OnlySelect_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "Select   abcd";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "Select a123 ";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "Select s";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestSelectOverallRegex_OnlySelect_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "select s1@";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "selects10";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "selects10";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "select s10 suchthat";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "Select abcd such that";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestSelectOverallRegex_SelectAndUses_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(a,b)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
            qvf = QueryValidatorFriend();
            str = "Select s12 such that Uses ( b , c )";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestSelectOverallRegex_SelectAndPattern_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s12 pattern a ( _ , _ ) ";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

              
        /****************
        * Pattern Tests *
        ****************/
        TEST_METHOD(TestRegex_Pattern_Synonym_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Synonym_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _\"x\"_)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Underscore_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, _\"x\"_)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Ident_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"y\", _\"x\"_)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, _)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Ident_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"y\", _)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
        }

        TEST_METHOD(TestRegex_Pattern_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(validBothArgs, _)";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
            str = "pattern a (   validBothArgs  ,   _  )";
            Assert::IsTrue(qvf.isValidPatternRegex(str));
            /*str = "pattern a(_, "a+b");
            Assert::IsTrue(qvf.isValidPatternRegex(str));
            */
        }

        TEST_METHOD(TestRegex_Pattern_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "Pattern a(uppercase, _\"relationshipName\"_)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "misspelt(relationship, _\"name\"_)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(v_\"validExpressionSpec\"_, _)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern (noSynonymBeforeBracket, _)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(invalidSecondArg,2)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a[validArgsSyntax, _\"wrongBrackets\"_";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(validArgsSyntax noCommas)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
            str = "pattern a(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qvf.isValidPatternRegex(str));
        }

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

        TEST_METHOD(TestRegex_Factor_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "#invalidNameInvalidInteger";
            Assert::IsFalse(qvf.isValidFactor(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
            str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_UnderscoreFactorUnderscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(qvf.isValidExpressionSpec(str));
        }

        TEST_METHOD(TestRegex_ExpressionSpec_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
            str = "_\"validFactorWithLeftSideUnderscoreOnly\"";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
            str = "\"validFactorWithRightSideUnderscoreOnly\"_";
            Assert::IsFalse(qvf.isValidExpressionSpec(str));
        }


        /******************************
        * Entire query Validity Tests *
        ******************************/
        TEST_METHOD(TestQueryValidity)
        {
            QueryValidator qv;
            string query = "assign a; variable v; Select v";

            Assert::IsTrue(qv.isValidQuery(query));
        }


    };
}