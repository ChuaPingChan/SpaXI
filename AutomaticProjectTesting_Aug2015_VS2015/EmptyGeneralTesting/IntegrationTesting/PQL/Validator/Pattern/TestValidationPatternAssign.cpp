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
        string str;
        QueryTree *qtPtr;
        PatternHandler pHandler = PatternHandler(qtPtr);

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            pHandler = PatternHandler(qtPtr);
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_Underscore_Valid)
        {
            str = "a(v, _)";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            str = "a(v, _\"x\"_)";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            str = "a(v, \"x\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            str = "a(_, _\"x\"_)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            str = "a(_, \"x\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            str = "a(\"x\", _\"x\"_)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", EXPRESSION_SPEC_PARTIAL, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_ExpressionSpec_ExactMatch_SingleVariable_Valid)
        {
            str = "a(\"x\", \"x\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", EXPRESSION_SPEC_EXACT, "x");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Underscore_Valid)
        {
            str = "a(_, _)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IdentWithQuotes_Underscore_Valid)
        {
            str = "a(\"x\", _)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_SingleOperator_PartialMatch_Valid)
        {
            str = "a(v, _\"x+y\"_)";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x+y");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_SingleOperator_ExactMatch_Valid)
        {
            str = "a(v, \"x+y\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x+y");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiVariable_MultiOperator_ExactMatch_Valid)
        {
            str = "a(v, \"x+y-z*a\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x+y-z*a");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_MultiInteger_MultiOperator_ExactMatch_Valid)
        {
            str = "a(v, \"1+3*4-9\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "1+3*4-9");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExtendedComplexExpression_NoBrackets_ExactMatch_Valid)
        {
            str = "a(v, \"hell0+15-m3*im-w0ndering-a11+th353*y3ars-youd+lik3*2*m33t\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "hell0+15-m3*im-w0ndering-a11+th353*y3ars-youd+lik3*2*m33t");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_ExtendedComplexExpression_WithBrackets_ExactMatch_Valid)
        {
            str = "a(v, \"(1-(wanna+(b3*(th3-very+best)-like*(no+one*ever-was)))*To-catch+them+is-((my*real+test)*ToTrainThem+isMyCause))\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "(1-(wanna+(b3*(th3-very+best)-like*(no+one*ever-was)))*To-catch+them+is-((my*real+test)*ToTrainThem+isMyCause))");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_FirstArg_NotVariable_Invalid)
        {
            str = "a(cl, _)";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_TooManyArguments_Invalid)
        {
            str = "a(_, _, _)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestRegex_Pattern_Assign_IncorrectSumOfBrackets_OkInRegex_Valid)
        {
            str = "   a(v, \"(((1+2)\")   ";
            qtPtr->insertSynonym(ASSIGN, "a");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}