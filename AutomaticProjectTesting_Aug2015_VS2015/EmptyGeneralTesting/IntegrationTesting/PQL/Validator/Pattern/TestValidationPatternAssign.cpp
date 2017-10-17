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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_EXACT, "x");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC_PARTIAL, "x");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", EXPRESSION_SPEC_PARTIAL, "x");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", UNDERSCORE, "_", UNDERSCORE, "_");
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
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", IDENT_WITHQUOTES, "x", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Synonym_ExpressionSpec_PartialMatch_MultiVariable_Valid)
        {
            string str = "a(v, _\"x+y\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC_PARTIAL, "x+y");
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

        TEST_METHOD(TestValidity_Pattern_Assign_WhitespaceBtwnIntegers_Invalid)
        {
            string str = "a(v, \"1 + a + 2 3 + c\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
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