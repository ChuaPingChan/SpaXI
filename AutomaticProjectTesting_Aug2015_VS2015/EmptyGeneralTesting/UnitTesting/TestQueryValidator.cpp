#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestQueryValidator)
    {
    public:
        /*--------------- Grammar Regex Test---------------*/
        TEST_METHOD(TestLetterRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Letter Regex
            str = "a";
            Assert::IsTrue(qv.isValidLetterTest(str));

            //Invalid Letter Regex
            str = "invalid";
            Assert::IsFalse(qv.isValidLetterTest(str));
            str = "#";
            Assert::IsFalse(qv.isValidLetterTest(str));
            str = "2";
            Assert::IsFalse(qv.isValidLetterTest(str));
            str = " ";
            Assert::IsFalse(qv.isValidLetterTest(str));
            str = "";
            Assert::IsFalse(qv.isValidLetterTest(str));
        }

        TEST_METHOD(TestIntegerRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Integer Regex
            str = "1";
            Assert::IsTrue(qv.isValidIntegerTest(str));
            str = "0123";
            Assert::IsTrue(qv.isValidIntegerTest(str));

            //Invalid Integer Regex
            str = "invalid integer";
            Assert::IsFalse(qv.isValidIntegerTest(str));
            str = "_";
            Assert::IsFalse(qv.isValidIntegerTest(str));
            str = " ";
            Assert::IsFalse(qv.isValidIntegerTest(str));
            str = "";
            Assert::IsFalse(qv.isValidLetterTest(str));
        }

        TEST_METHOD(TestSynonymRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Synonym Regex
            str = "a";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameWith#SymbolWithoutNumbers";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameW1thNumb3rAnd#Symbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "assign";
            Assert::IsTrue(qv.isValidSynonymTest(str));

            //Invalid Synonym Regex
            str = "0";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "#";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidSynonymTest(str));
        }

        TEST_METHOD(TestStmtRefRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Stmt Ref Regex
            str = "validSynonym";
            Assert::IsTrue(qv.isValidStmtRefTest(str));
            str = "_";
            Assert::IsTrue(qv.isValidStmtRefTest(str));
            str = "22011209040009142005070518";
            Assert::IsTrue(qv.isValidStmtRefTest(str));

            //Invalid Stmt Ref Regex
            str = "validSynonym_validUnderscore_22011209040009142005070518";
            Assert::IsFalse(qv.isValidStmtRefTest(str));
            str = "\"validIdentWithQuotationMarks\"";
            Assert::IsFalse(qv.isValidStmtRefTest(str));
        }

        TEST_METHOD(TestEntRefRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Ent Ref Regex
            str = "validSynonym";
            Assert::IsTrue(qv.isValidEntRefTest(str));
            str = "_";
            Assert::IsTrue(qv.isValidEntRefTest(str));
            str = "\"validIdentWithQuotationMarks\"";
            Assert::IsTrue(qv.isValidEntRefTest(str));

            //Invalid Ent Ref Regex
            str = "validSynonym_validUnderscore_\"validIdentW1thQu0tationMarks\"";
            Assert::IsFalse(qv.isValidStmtRefTest(str));
        }

        TEST_METHOD(TestNameRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Name Regex
            str = "a";
            Assert::IsTrue(qv.isValidNameTest(str));
            str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qv.isValidNameTest(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qv.isValidNameTest(str));
            str = "assign";
            Assert::IsTrue(qv.isValidNameTest(str));

            //Invalid Name Regex
            str = "0";
            Assert::IsFalse(qv.isValidNameTest(str));
            str = "#";
            Assert::IsFalse(qv.isValidNameTest(str));
            str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qv.isValidNameTest(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidNameTest(str));
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
            vector<string> inputVector;

            inputVector.push_back("assign a");
            inputVector.push_back("variable v");
            inputVector.push_back("Select v");

            Assert::IsTrue(qv.isValidQuery(inputVector));
        }

    };
}