#include <string>
#include <cstdio>
#include <regex>

#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"
#include "../SPA/PKB/PKBMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const std::string dummySimpleSourcePath = "../UnitTesting/ParserTestDependencies/dummySimpleSource.txt";
PKBMain dummyPkbMain;
PKBMain* dummyPkbMainPtr = &dummyPkbMain;

namespace UnitTesting
{

    TEST_CLASS(TestParser)
    {
    public:
        TEST_METHOD(regexValidEntityNameTest)
        {
            Assert::IsFalse(std::regex_match("", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match(" ", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match("1", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match("+", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match("a_b", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match("a&", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match("a", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match("A", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match("a1", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match("abc34", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match("\n\t\r\f abc34 \n\t\r\f", Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsFalse(std::regex_match("abc34 def", Parser::REGEX_VALID_ENTITY_NAME));
        }

        TEST_METHOD(regexMatchConstantTest)
        {
            Assert::IsFalse(std::regex_match("", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsFalse(std::regex_match(" \n\t\r", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsFalse(std::regex_match("%", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsFalse(std::regex_match("1$", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(std::regex_match("1", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(std::regex_match("123", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(std::regex_match("\t\n\r  123  \t\n\r", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsFalse(std::regex_match("123 456", Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(std::regex_match("112324324713134813471346450953542945792548724958", Parser::REGEX_MATCH_CONSTANT));
        }

        TEST_METHOD(regexExtractUpToSemiColonTest)
        {
            std::string targetString, expectedString;
            std::smatch match;

            targetString = "abc;";
            expectedString = "abc";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));
            Assert::IsTrue((match.str(1) == expectedString));

            targetString = " a = 1;";
            expectedString = "a = 1";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));
            Assert::IsTrue((match.str(1) == expectedString));

            targetString = ";";
            Assert::IsFalse(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));
            targetString = "should fail";
            Assert::IsFalse(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));

            targetString = "   ;";
            Assert::IsFalse(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));

            targetString = "    this\t\n\r \t\n\rshould\f \fpass\n; redundant words and semicolons ; ; ; ";
            expectedString = "this\t\n\r \t\n\rshould\f \fpass\n";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_UP_TO_SEMICOLON));
            Assert::IsTrue((match.str(1) == expectedString));
        }

        TEST_METHOD(regexMatchProcedureKeywordTest)
        {
            Assert::IsTrue(std::regex_match("procedure", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsTrue(std::regex_match(" \t\n\r\fprocedure\t\n\r\f ", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsFalse(std::regex_match("procedureFirst", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsFalse(std::regex_match("procedur", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsFalse(std::regex_match("proc3dure", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsFalse(std::regex_match("", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsFalse(std::regex_match("   ", Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
        }

        TEST_METHOD(regexMatchWhileKeywordTest)
        {
            Assert::IsTrue(std::regex_match("while", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsTrue(std::regex_match(" \t\n\r\fwhile\t\n\r\f ", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsFalse(std::regex_match("whilei", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsFalse(std::regex_match("whil", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsFalse(std::regex_match("whi le", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsFalse(std::regex_match("", Parser::REGEX_MATCH_WHILE_KEYWORD));
            Assert::IsFalse(std::regex_match("   ", Parser::REGEX_MATCH_WHILE_KEYWORD));
        }

        TEST_METHOD(regexMatchBracesBracketsAndSemiColonsTest)
        {
            Assert::IsTrue(std::regex_match("{", Parser::REGEX_MATCH_OPEN_BRACE));
            Assert::IsTrue(std::regex_match(" \t\n\r\f{\t\n\r\f ", Parser::REGEX_MATCH_OPEN_BRACE));
            Assert::IsFalse(std::regex_match(" {a ", Parser::REGEX_MATCH_OPEN_BRACE));
            Assert::IsFalse(std::regex_match(" a{ ", Parser::REGEX_MATCH_OPEN_BRACE));

            Assert::IsTrue(std::regex_match("}", Parser::REGEX_MATCH_CLOSE_BRACE));
            Assert::IsTrue(std::regex_match(" \t\n\r\f}\t\n\r\f ", Parser::REGEX_MATCH_CLOSE_BRACE));
            Assert::IsFalse(std::regex_match(" }a ", Parser::REGEX_MATCH_CLOSE_BRACE));
            Assert::IsFalse(std::regex_match(" a} ", Parser::REGEX_MATCH_CLOSE_BRACE));

            Assert::IsTrue(std::regex_match("(", Parser::REGEX_MATCH_OPEN_BRACKET));
            Assert::IsTrue(std::regex_match(" \t\n\r\f(\t\n\r\f ", Parser::REGEX_MATCH_OPEN_BRACKET));
            Assert::IsFalse(std::regex_match(" (a ", Parser::REGEX_MATCH_OPEN_BRACKET));
            Assert::IsFalse(std::regex_match(" a( ", Parser::REGEX_MATCH_OPEN_BRACKET));

            Assert::IsTrue(std::regex_match(")", Parser::REGEX_MATCH_CLOSE_BRACKET));
            Assert::IsTrue(std::regex_match(" \t\n\r\f)\t\n\r\f ", Parser::REGEX_MATCH_CLOSE_BRACKET));
            Assert::IsFalse(std::regex_match(" )a ", Parser::REGEX_MATCH_CLOSE_BRACKET));
            Assert::IsFalse(std::regex_match(" a) ", Parser::REGEX_MATCH_CLOSE_BRACKET));

            Assert::IsTrue(std::regex_match(";", Parser::REGEX_MATCH_SEMICOLON));
            Assert::IsTrue(std::regex_match(" \t\n\r\f;\t\n\r\f ", Parser::REGEX_MATCH_SEMICOLON));
            Assert::IsFalse(std::regex_match(" ;a ", Parser::REGEX_MATCH_SEMICOLON));
            Assert::IsFalse(std::regex_match(" a; ", Parser::REGEX_MATCH_SEMICOLON));
        }

        TEST_METHOD(regexMatchEqualAndOtherOperatorsTest)
        {
            Assert::IsTrue(std::regex_match("=", Parser::REGEX_MATCH_EQUAL));
            Assert::IsTrue(std::regex_match("+ ", Parser::REGEX_VALID_OPERATOR));
            Assert::IsTrue(std::regex_match(" -", Parser::REGEX_VALID_OPERATOR));
            Assert::IsTrue(std::regex_match("\n\t*\n\t", Parser::REGEX_VALID_OPERATOR));
            Assert::IsTrue(std::regex_match("\r\f/\r\f", Parser::REGEX_VALID_OPERATOR));

            Assert::IsFalse(std::regex_match("a=4", Parser::REGEX_VALID_OPERATOR));
            Assert::IsFalse(std::regex_match("+-", Parser::REGEX_VALID_OPERATOR));
            Assert::IsFalse(std::regex_match("9+3", Parser::REGEX_VALID_OPERATOR));
            Assert::IsFalse(std::regex_match("-;", Parser::REGEX_VALID_OPERATOR));
        }

        TEST_METHOD(regexMatchExpressionLhsRhsTest)
        {
            Assert::IsTrue(std::regex_match("a+b", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match("a -   b", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match("\na\t*\nb\t", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match(" \ra\f /  \rb\f ", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match(" 6 + 3 * 4", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match(" 6 + 3 \t\r\n* \t\r\n4\t\r\n", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));

            Assert::IsFalse(std::regex_match("=4", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsFalse(std::regex_match("+-", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsFalse(std::regex_match("9+", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsFalse(std::regex_match("-;", Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
        }

        TEST_METHOD(regexExtractExpressionLhsRhsTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);

            std::cmatch match;
            Assert::IsTrue(std::regex_match("a+b", match, Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue("a" == match.str(1));
            Assert::IsTrue("b" == match.str(2));

            Assert::IsTrue(std::regex_match("\t\n  \ra\r\t\f + \f\t\r b\t", match, Parser::REGEX_EXTRACT_EXPRESSION_LHS_RHS));
            Assert::IsTrue(std::regex_match(match.str(1), Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(std::regex_match(match.str(2), Parser::REGEX_VALID_ENTITY_NAME));

        }

        TEST_METHOD(regexExtractBracketWrappedContent)
        {
            std::string targetString, expectedString, actualString;
            std::smatch match;

            targetString = "(abcd)";
            expectedString = "abcd";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);

            targetString = "(a + 2 * 3)";
            expectedString = "a + 2 * 3";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue( actualString == expectedString);

            targetString = "((a + 2 * 3))";
            expectedString = "(a + 2 * 3)";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);

            targetString = "\t ((a + 2 * 3)) \t\r";
            expectedString = "(a + 2 * 3)";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);

            targetString = "((a + 2) * 3)";
            expectedString = "(a + 2) * 3";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);

            targetString = "(a + (2 * 3))";
            expectedString = "a + (2 * 3)";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);

            targetString = "((a + b) + (2 * 3))";
            expectedString = "(a + b) + (2 * 3)";
            Assert::IsTrue(std::regex_match(targetString, match, Parser::REGEX_EXTRACT_BRACKET_WRAPPED_CONTENT));
            actualString = match.str(1);
            Assert::IsTrue(actualString == expectedString);
        }

        TEST_METHOD(getNextTokenTest_matchTokenTest_assertMatchAndIncrTokenTest)
        {
            // Set up
            ParserChildForTest parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());
            Assert::IsTrue(parser.concatenateLines(dummySimpleSourcePath));

            // Testing begins
            Assert::IsTrue(parser.incrCurrentTokenPtr());
            Assert::IsTrue(parser.matchToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_PROCEDURE_KEYWORD));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_MATCH_OPEN_BRACE));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_VALID_ENTITY_NAME));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_MATCH_EQUAL));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_EQUAL));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_CONSTANT));
            Assert::IsTrue(parser.matchToken(Parser::REGEX_MATCH_SEMICOLON));
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(tokenizeStringTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);
            std::string stringToTokenize = "one two three ; 123 { } a45=";
            std::vector<std::string> expectedTokens = { "one", "two", "three", ";", "123", "{", "}", "a45", "=" };
            std::vector<std::string> actualTokens = parser.tokenizeString(stringToTokenize);
            Assert::IsTrue(actualTokens == expectedTokens);
        }

        TEST_METHOD(extractStringUpToSemicolonTest)
        {
            // Set up
            ParserChildForTest parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());
            Assert::IsTrue(parser.concatenateLines(dummySimpleSourcePath));

            // Testing begins
            for (int i = 0; i < 4; i++) {
                parser.incrCurrentTokenPtr();  // Skip procedure header to assignment stmt.
            }

            std::string charsUpTillSemiColon = parser.extractStringUpToSemicolon();
            std::vector<std::string> expectedTokens = { "a", "=", "1" };
            std::vector<std::string> actualTokens = parser.tokenizeString(charsUpTillSemiColon);
            Assert::IsTrue(actualTokens == expectedTokens);

            // Going to the next assignment stmt
            while (!parser.matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
                parser.incrCurrentTokenPtr();
            }
            Assert::IsTrue(parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON));

            charsUpTillSemiColon = parser.extractStringUpToSemicolon();
            expectedTokens = { "b", "=", "2" };
            actualTokens = parser.tokenizeString(charsUpTillSemiColon);
            Assert::IsTrue(actualTokens == expectedTokens);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(assignmentAndWhileExpectedTest)
        {
            // Set up
            ParserChildForTest parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());
            Assert::IsTrue(parser.concatenateLines(dummySimpleSourcePath));

            // Go to first assignment statement
            while (!parser.matchToken(Parser::REGEX_MATCH_OPEN_BRACE)) {
                parser.incrCurrentTokenPtr();
            }
            parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_OPEN_BRACE);
            Assert::IsTrue(parser.assignmentExpected());

            // Go to next assignment statement
            while (!parser.matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
                parser.incrCurrentTokenPtr();
            }
            parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);
            Assert::IsTrue(parser.assignmentExpected());

            // Go to while statement
            for (int i = 0; i < 2; i++) {
                while (!parser.matchToken(Parser::REGEX_MATCH_SEMICOLON)) {
                    parser.incrCurrentTokenPtr();
                }
                parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_SEMICOLON);
            }
            Assert::IsTrue(parser.whileExpected());

            // Go to another while statement
            while (!parser.matchToken(Parser::REGEX_MATCH_CLOSE_BRACE)) {
                parser.incrCurrentTokenPtr();
            }
            parser.assertMatchAndIncrementToken(Parser::REGEX_MATCH_CLOSE_BRACE);
            Assert::IsTrue(parser.whileExpected());

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(assertIsValidExpressionTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);
            Assert::IsTrue(parser.assertIsValidExpression("a"));
            Assert::IsTrue(parser.assertIsValidExpression("1"));
            Assert::IsFalse(parser.assertIsValidExpression(""));
            Assert::IsFalse(parser.assertIsValidExpression(" "));
            Assert::IsFalse(parser.assertIsValidExpression("+"));
            Assert::IsFalse(parser.assertIsValidExpression("+a"));
            Assert::IsFalse(parser.assertIsValidExpression("b +"));
            Assert::IsFalse(parser.assertIsValidExpression("$"));
            Assert::IsFalse(parser.assertIsValidExpression("\n\t\r"));
            Assert::IsTrue(parser.assertIsValidExpression("a+b"));
            Assert::IsTrue(parser.assertIsValidExpression("a + b  "));
            Assert::IsFalse(parser.assertIsValidExpression("a + 3b  "));
            Assert::IsFalse(parser.assertIsValidExpression("a + a%b  "));
            Assert::IsFalse(parser.assertIsValidExpression("a_c + b  "));
            Assert::IsTrue(parser.assertIsValidExpression("\n\t\r a \n\n\t + \t\r\n\fb  \n\t\r"));
            Assert::IsTrue(parser.assertIsValidExpression("a - b  "));
            Assert::IsTrue(parser.assertIsValidExpression("a * b  "));
            Assert::IsTrue(parser.assertIsValidExpression("a / b  "));
            Assert::IsFalse(parser.assertIsValidExpression("a +/ b  "));
            Assert::IsTrue(parser.assertIsValidExpression("a + b  - 3"));
            Assert::IsTrue(parser.assertIsValidExpression("a + b/3 * 2 / d + b  "));
            Assert::IsTrue(parser.assertIsValidExpression("a134124 + b/3 * 2  "));
            Assert::IsFalse(parser.assertIsValidExpression(" a = 3 + 4 "));
            Assert::IsFalse(parser.assertIsValidExpression(" 3 + 4 ; "));
            Assert::IsFalse(parser.assertIsValidExpression("()"));
            Assert::IsTrue(parser.assertIsValidExpression("(a)"));
            Assert::IsTrue(parser.assertIsValidExpression(" (3+4) "));
            Assert::IsFalse(parser.assertIsValidExpression("4(1+2)"));
            Assert::IsTrue(parser.assertIsValidExpression(" 3 +  4 "));
            Assert::IsTrue(parser.assertIsValidExpression(" ( 3 +  4 ) "));
            Assert::IsFalse(parser.assertIsValidExpression("( 3 +  4 - () )"));
            Assert::IsTrue(parser.assertIsValidExpression(" 4 - 3 * \n\t6\t "));
            Assert::IsTrue(parser.assertIsValidExpression("3 * \n\t6\t "));
            /*Assert::IsTrue(parser.assertIsValidExpression("((2) + (4 - 3) * \n\t(6)\t )\t\n"));
            Assert::IsFalse(parser.assertIsValidExpression("((2) + (4 - 3)) * \n\t((6)\t \t\n"));
            Assert::IsFalse(parser.assertIsValidExpression("b + (x+(3+b)) + a (("));*/

        }

        TEST_METHOD(removeAllWhiteSpacesTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);
            std::string withWhiteSpace;
            std::string noWhiteSpace;

            withWhiteSpace = "  \n3\r\f + 4 \n\t ";
            noWhiteSpace = "3+4";
            Assert::IsTrue(noWhiteSpace == parser.removeAllWhitespaces(withWhiteSpace));

            withWhiteSpace = "    ";
            noWhiteSpace = "";
            Assert::IsTrue(noWhiteSpace == parser.removeAllWhitespaces(withWhiteSpace));

            withWhiteSpace = "3+4*8/5";
            noWhiteSpace = "3+4*8/5";
            Assert::IsTrue(noWhiteSpace == parser.removeAllWhitespaces(withWhiteSpace));

            withWhiteSpace = " a + (c-\n   \td) *e    \n\t";
            noWhiteSpace = "a+(c-d)*e";
            Assert::IsTrue(noWhiteSpace == parser.removeAllWhitespaces(withWhiteSpace));
            withWhiteSpace = noWhiteSpace;
            Assert::IsTrue(noWhiteSpace == parser.removeAllWhitespaces(withWhiteSpace));
        }

        TEST_METHOD(removeAllBracketsTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);
            std::string withBrackets;
            std::string noBrackets;

            withBrackets = "  \n(3\r\f + 4) \n\t ";
            noBrackets = "  \n3\r\f + 4 \n\t ";
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));

            withBrackets = "()";
            noBrackets = "";
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));

            withBrackets = "3+4*8/5";
            noBrackets = "3+4*8/5";
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));

            withBrackets = " (3 +  4) ";
            noBrackets = " 3 +  4 ";
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));

            withBrackets = "(a+(((c)-(d))*e))";
            noBrackets = "a+c-d*e";
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));
            withBrackets = noBrackets;
            Assert::IsTrue(noBrackets == parser.removeAllBrackets(withBrackets));
        }

        TEST_METHOD(isBracketedCorrectlyTest)
        {
            ParserChildForTest parser(dummyPkbMainPtr);
            std::string expression;

            expression = "  \n3\r\f + 4 \n\t ";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "3 + 4";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = " ( ";
            Assert::IsFalse(parser.isBracketedCorrectly(expression));
            expression = " ) ";
            Assert::IsFalse(parser.isBracketedCorrectly(expression));
            expression = "(3 + 4)";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "(3 + 4";
            Assert::IsFalse(parser.isBracketedCorrectly(expression));
            expression = "3 + 4)";
            Assert::IsFalse(parser.isBracketedCorrectly(expression));
            expression = "(3 - (4 / \t\n(2) * 5)+ 4)";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "((()))";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "(()())";
            Assert::IsTrue(parser.isBracketedCorrectly(expression));
            expression = "((())))";
            Assert::IsFalse(parser.isBracketedCorrectly(expression));
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_equalSignMissing)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingEqual());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_missingSemicolon)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingSemicolon());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_wrongProcName)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_wrongProcName());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_whileOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_whileOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile2_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile2());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            
            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_missingBoolVar)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile_missingBoolVar());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd2LevelNestedWhile_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_2LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_prototypeStandard_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_prototypeStandard());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsCalls_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsAndCalls());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /******************************
        * Utility Methods for Testing *
        *******************************/
        TEST_METHOD(testDummySimpleSourceFileUtilityMethods)
        {
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_nonNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_2LevelNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only.
        */
        bool createDummySimpleSourceFile_assignmentsOnly() {
            std::string content = "procedure ABC{\n  a = 1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with syntax error.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_missingEqual() {
            std::string content = "procedure ABC{\n  a  1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with missing semicolon.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_missingSemicolon() {
            std::string content = "procedure ABC{\n  a = 1;\n b = 2;\n	c = a\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with wrong procedure name.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_wrongProcName() {
            std::string content = "procedure 3abc {\n  a  1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and a while loop without nesting.
        */
        bool createDummySimpleSourceFile_whileOnly() {
            std::string content = "procedure ABC { \ni = j; \nj = 3 + 5; \nwhile a \n{ \n	a = 3; \n   b = 2  ; \nc = 4; \nd = 5; \n} \nc = c + d; \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and a while loop without nesting.
        */
        bool createDummySimpleSourceFile_assignments_nonNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n	a = 3; \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n		a = b; \n		c = 3; \n		d = 4; \n        while tmp{ \n		d = c + a; \n		e = d + 3 + 4 * 5; \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n	c = 3 + a * e + d; \n        x = x + 1;} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile2() {
            std::string content = "procedure One { \n	a = a + b + c + c + b + a; \n \n	while c { \n		c = a + b; \n	} \n \n	while c { \n		while b { \n			a = a + b + c + c + b + a; \n			b = b + b; \n		} \n	} \n}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        Missing boolean variable in while statement header.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile_missingBoolVar() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile  \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n		a = b; \n		c = 3; \n		d = 4; \n        while tmp{ \n		d = c + a; \n		e = d + 3 + 4 * 5; \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n	c = 3 + a * e + d; \n        x = x + 1;} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 2-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_2LevelNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n        while tmp{ \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n        x = x + 1; \n        while left { \n            x = x+ 1	; }} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 2-level nested while loops.
        The dummy SIMPLE program is up to the standard of iteration1.0 testing.
        */
        bool createDummySimpleSourceFile_prototypeStandard() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n        while tmp{ \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n        x = x + 1; \n        while left { \n          while right { \n            Romeo = Romeo + 1; \n			f = 3; \n            b = 0; \n            c = delta    + l  + width + Romeo ; } \n            while c { \n			b = d + 1; \n			g = 3 + 2; \n              c = c +1   	; } \n			c = b - 5; \n			b = c - a; \n            x = x+ 1	; }} \n		e = g - 1; \n          a=   2; } \n   w = w+1  ; \n   w = 2		; \n   i = w; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source with
        multiple procedures, all containing assignment statements only.
        */
        bool createDummySimpleSourceFile_multiProcs_assignmentsOnly() {
            std::string content = "procedure ABC{ \n  a = 1; \n b = 2; \n	c = a; \n } \n \nprocedure DEF{ \n  a = 1; \n b = 2; \n	c = a; \n } \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source with
        multiple procedures, all containing assignment statements and
        valid call statements only.
        */
        bool createDummySimpleSourceFile_multiProcs_assignmentsAndCalls() {
            std::string content = "procedure ABC{ \n  a = 1; \n b = 2; \n call DEF; \n	c = a; \n } \n \nprocedure DEF{ \n  a = 1; \n b = 2; \n	c = a; \n } \n ";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        // This is a utility method to destroy the dummy text file created by createDummyTextFile()
        bool deleteDummySimpleSourceFile() {
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            return std::remove(newFilePath.c_str()) == 0;
        }
    };
}