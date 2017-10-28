#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Patternship.h"
#include "..\SPA\PQL\Validator\Selection\Pattern\PatternHandler.h"
#include "..\SPA\PQL\Utilities\PatternClause.h"
#include "..\..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/*
* This class assumes that the overall pattern regex passed, hence only check for the assign component
* The keyword, 'pattern', has been removed 
*/

namespace UnitTesting
{
    TEST_CLASS(TestValidationPatternAssign)
    {
    public:
        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_Underscore_Valid)
        {
            string str = "a(v, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "a(v, _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            string str = "a(v, \"x\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "a(_, _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            string str = "a(_, \"x\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "a(\"x\", _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            string str = "a(\"x\", \"x\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Underscore_Valid)
        {
            string str = "a(_, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_Underscore_Valid)
        {
            string str = "a(\"x\", _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_SingleOperator_PartialMatch_Valid)
        {
            string str = "a(v, _\"x+y\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x+y");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_SingleOperator_ExactMatch_Valid)
        {
            string str = "a(v, \"x+y\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x+y");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_MultiOperator_ExactMatch_Valid)
        {
            string str = "a(v, \"x+y-z*a\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x+y-z*a");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiInteger_MultiOperator_ExactMatch_Valid)
        {
            string str = "a(v, \"1+3*4-9\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "1+3*4-9");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExtendedComplexExpression_NoBrackets_ExactMatch_Valid)
        {
            string str = "a(v, \"hell0+15-m3*im-w0ndering-a11+th353*y3ars-youd+lik3*2*m33t\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "hell0+15-m3*im-w0ndering-a11+th353*y3ars-youd+lik3*2*m33t");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExtendedComplexExpression_WithBrackets_ExactMatch_Valid)
        {
            string str = "a(v, \"(1-(wanna+(b3*(th3-very+best)-like*(no+one*ever-was)))*To-catch+them+is-((my*real+test)*ToTrainThem+isMyCause))\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "(1-(wanna+(b3*(th3-very+best)-like*(no+one*ever-was)))*To-catch+them+is-((my*real+test)*ToTrainThem+isMyCause))");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_FirstArg_NotVariable_Invalid)
        {
            string str = "a(cl, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(CALL, "cl");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_TooManyArguments_Invalid)
        {
            string str = "a(_, _, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestRegex_Pattern_Assign_IncorrectSumOfBrackets_OkInRegex_Valid)
        {
            string str = "   a(v, \"(((1+2)\")   ";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}