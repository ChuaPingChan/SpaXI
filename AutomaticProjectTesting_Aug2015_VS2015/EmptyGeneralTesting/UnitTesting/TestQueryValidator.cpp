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


































		TEST_METHOD(TestRemoveAllSpaces)
		{
			QueryValidator qv;
			string str;

			str = " a  b    c  ";
			Assert::IsTrue(qv.removeAllSpacesTest(str) == "abc");
		}

       

        /*--------------- Substring Test---------------*/

        TEST_METHOD(TestSubstringBetweenDelims) 
        {
            QueryValidator qv;
            string str;
            
            //Uses clause test
            qv = QueryValidator();
            str = "Uses(a,b)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str,"(",",","a"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, ",", ")", "b"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, "(", ",", "(a"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", ",", "a"));

            //Modifies clause test
            qv = QueryValidator();
            str = "Modifes(abc,def)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "abc"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, ",", ")", "def"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, "(", ",", "(awf"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", "31", "awfwf"));

            //Follows and Follows* clause test
            qv = QueryValidator();
            str = "Follows(a,b)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "a"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", ",", "qeeq"));
            qv = QueryValidator();
            str = "Follows*(123,456)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "123"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", "rwr", "3121"));
			qv = QueryValidator();
			str = "Follows*(s1, s2)";
			Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "s1"));
			Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", "rwr", "3121"));

            //Parent and Parent* clause test
            qv = QueryValidator();
            str = "Parent(abc123,def)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "abc123"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", "\"", "qeeq"));
            qv = QueryValidator();
            str = "Parent*(1,2)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "Parent", "(", "*"));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", "2", ","));

            //Pattern clause test
            qv = QueryValidator();
            str = "patternarg1(arg2,arg3)";
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "pattern", "(", "arg1"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "(", ",", "arg2"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, ",", ")", "arg3"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "ern", "(", "arg1"));
            Assert::IsTrue(qv.isGetBetweenTwoStringsTest(str, "arg2", "arg3", ","));
            Assert::IsFalse(qv.isGetBetweenTwoStringsTest(str, ",", ")", "arg2"));



        }

        /*--------------- Declaration Test---------------*/
        TEST_METHOD(TestEntityRegex)
        {
            QueryValidator qv;
            string str;
            
            //Valid Entities Regex
            str = "procedure";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "stmtLst";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "stmt";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "assign";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "call";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "while";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "if";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "variable";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "constant";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "prog_line";
            Assert::IsTrue(qv.isValidEntityTest(str));

            //Invalid Entities Regex
            str = "invalidEntity";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "invalidEntityEndsWith#";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "invalidEntityEndsWith1";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidEntityTest(str));
        }

        TEST_METHOD(TestQueryDeclarationValidity)
        {
            QueryValidator qv;
            string str;

            //Valid Declaration
            str = "assign validEntityAndSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity  , separatedByComma ,      multipleValidSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity, mixedCommaFormat     ,      multipleVa1idSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(qv.isValidDeclarationTest(str));

            //Invalid Declaration
            qv = QueryValidator();
            str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "invalidEntity validSynonym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity, inv@lidSynonym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity, validSynonymRepeted, validSynonymRepeted";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
        }


        /*--------------- Pattern Test---------------*/
        TEST_METHOD(TestFactorRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Factor Regex
            str = "validName";
            Assert::IsTrue(qv.isValidFactorTest(str));
            str = "22011209040009142005070518";
            Assert::IsTrue(qv.isValidFactorTest(str));
            str = "validName22011209040009142005070518";
            Assert::IsTrue(qv.isValidFactorTest(str));

            //Invalid Factor Regex
            str = "#invalidNameInvalidInteger";
            Assert::IsFalse(qv.isValidFactorTest(str));
        }

        TEST_METHOD(TestExpressionSpecRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Expression Regex
            str = "_";
            Assert::IsTrue(qv.isValidExpressionSpecTest(str));
            str = "_\"validFactorWithBothSideUnderscore\"_";
            Assert::IsTrue(qv.isValidExpressionSpecTest(str));
            /*str = "_\"validFactorWithLeftSideUnderscoreOnly\"";
            Assert::IsTrue(qv.isValidExpressionSpecTest(str));
            str = "\"validFactorWithRightSideUnderscoreOnly\"_";
            Assert::IsTrue(qv.isValidExpressionSpecTest(str));*/

            //Invalid Expression Regex
            str = "";
            Assert::IsFalse(qv.isValidExpressionSpecTest(str));
            //TODO: NEED MORE TEST CASES
        }

        TEST_METHOD(TestPatternRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Pattern Regex
            str = "pattern a(validBothArgs, _)";
            Assert::IsTrue(qv.isValidPatternRegexTest(str));
            str = "pattern a (   validBothArgs  ,   _  )";
            Assert::IsTrue(qv.isValidPatternRegexTest(str));
            /*str = "pattern a(_, "a+b");
            Assert::IsTrue(qv.isValidPatternRegexTest(str));
            */

            //Invalid Pattern Regex
            str = "Pattern a(uppercase, _\"relationshipName\"_)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "misspelt(relationship, _\"name\"_)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a(v_\"validExpressionSpec\"_, _)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern (noSynonymBeforeBracket, _)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a(invalidSecondArg,2)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a[validArgsSyntax, _\"wrongBrackets\"_";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a(validArgsSyntax noCommas)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
            str = "pattern a(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qv.isValidPatternRegexTest(str));
        }

        TEST_METHOD(TestPatternValidity)
        {
            QueryValidator qv;
            string str;

            //TODO: Test the validity for pattern
        }


        /*--------------- Relationship Test---------------*/
        TEST_METHOD(TestModifiesRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Modifies Regex
            str = "Modifies(validStmtRef,validEntRef)";
            Assert::IsTrue(qv.isValidModifiesRegexTest(str));
            str = "Modifies  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qv.isValidModifiesRegexTest(str));
            /*str = "Modifies(\"programName\", validEnrRef";
            Assert::IsTrue(qv.isValidModifiesRegexTest(str));*/

            //Invalid Modifies Regex
            str = "modifies(lowercase,relationshipName)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "misspelt(relationship,name)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "modifies(invalidSecondArg,2)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "Modifies[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "Modifies(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "Modifies(validArgsSyntax noCommas)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
            str = "Modifies(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qv.isValidModifiesRegexTest(str));
        }

        TEST_METHOD(TestUsesRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Uses Regex
            str = "Uses(validStmtRef,validEntRef)";
            Assert::IsTrue(qv.isValidUsesRegexTest(str));
            str = "Uses  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qv.isValidUsesRegexTest(str));
            /*str = "Uses(\"programName\", validEnrRef";
            Assert::IsTrue(qv.isValidUsesRegexTest(str));*/

            //Invalid Uses Regex
            str = "uses(lowercase,relationshipName)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "misspelt(relationship,name)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "uses(invalidSecondArg,2)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "Uses[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "Uses(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "Uses(validArgsSyntax noCommas)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
            str = "Uses(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qv.isValidUsesRegexTest(str));
        }

        TEST_METHOD(TestFollowsRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Follows||Follows* Regex
            str = "Follows(validStmtRef,validStmtRef)";
            Assert::IsTrue(qv.isValidFollowsRegexTest(str));
            str = "Follows  (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qv.isValidFollowsRegexTest(str));
            str = "Follows*(validStmtRef,validStmtRef)";
            Assert::IsTrue(qv.isValidFollowsRegexTest(str));
			str = "Follows*(s1, s2)";
			Assert::IsTrue(qv.isValidFollowsRegexTest(str));
            /*str = "Follows  *  (   validSynonymForBothArgs  ,   withWhiteSpacesBetweenFollowsAndStar   )";
            Assert::IsTrue(qv.isValidFollowsRegexTest(str));*/

            //Invalid Follows||Follows* Regex
            str = "follows(lowercase,relationshipName)";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
            str = "misspelt(relationship,name)";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
            str = "Follows[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
            str = "Follows(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
            str = "Follows(validArgsSyntax noCommas)";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
            str = "Follows(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qv.isValidFollowsRegexTest(str));
        }

        TEST_METHOD(TestParentRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Parent||Parent* Regex
            str = "Parent(validStmtRef,validStmtRef)";
            Assert::IsTrue(qv.isValidParentRegexTest(str));
            str = "Parent (   validSynonymForBothArgs  ,   withWhiteSpaces   )";
            Assert::IsTrue(qv.isValidParentRegexTest(str));
            str = "Parent*(validStmtRef,validStmtRef)";
            Assert::IsTrue(qv.isValidParentRegexTest(str));
            /*str = "Parent  *  (   validSynonymForBothArgs  ,   withWhiteSpacesBetweenParentAndStar   )";
            Assert::IsTrue(qv.isValidParentRegexTest(str));*/

            //Invalid Parent||Parent* Regex
            str = "parent(lowercase,relationshipName)";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
            str = "misspelt(relationship,name)";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
            str = "Parent[validArgsSyntax, wrongBrackets]";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
            str = "Parent(validArgsSyntax.butFullStopReplacesComma)";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
            str = "Parent(validArgsSyntax noCommas)";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
            str = "Parent(validArgsSyntax, with, multipleArgs)";
            Assert::IsFalse(qv.isValidParentRegexTest(str));
        }

        TEST_METHOD(TestModifiesValidity)
        {
            QueryValidator qv;
            string str;

            //TODO: Test validity of modifies
        }

        TEST_METHOD(TestUsesValidity)
        {
            QueryValidator qv;
            string str;

            //TODO: Test validity of uses
        }

        TEST_METHOD(TestFollowsValidity)
        {
            QueryValidator qv;
            string str;

            //TODO: Test validity of follows
        }

        TEST_METHOD(TestParentValidity)
        {
            QueryValidator qv;
            string str;

            //TODO: Test validity of parent
        }

        /*--------------- Select Test---------------*/
        TEST_METHOD(TestSelectOverallRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Select
            qv = QueryValidator();
            str = "Select s";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "Select   abcd";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "Select a123 ";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "Select s";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
            
            //Invalid Select
            qv = QueryValidator();
            str = "select s1@";
            Assert::IsFalse(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "selects10";
            Assert::IsFalse(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "selects10";
            Assert::IsFalse(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "select s10 suchthat";
            Assert::IsFalse(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "Select abcd such that";
            Assert::IsFalse(qv.isValidSelectOverallRegexTest(str));

            //Valid Select + Uses
            qv = QueryValidator();
            str = "Select s such that Uses(a,b)";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
            qv = QueryValidator();
            str = "Select s12 such that Uses ( b , c )";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));

            //Valid Select + pattern
            qv = QueryValidator();
            str = "Select s12 pattern a ( _ , _ ) ";
            Assert::IsTrue(qv.isValidSelectOverallRegexTest(str));
        }

        TEST_METHOD(TestQueryValidity)
        {
            QueryValidator qv;
			string query = "assign a; variable v; Select v";

            Assert::IsTrue(qv.isValidQuery(query));
        }

    };
}