#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Patternship.h"
#include "..\SPA\PQL\Validator\Selection\Pattern\PatternHandler.h"
#include "..\SPA\PQL\Utilities\PatternClause.h"
#include "..\..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationPatternAssign)
    {
    public:
        TEST_METHOD(TestValidity_PatternAssign_Synonym_Underscore_Valid)
        {
            string str = "pattern a(v, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_PatternAssign_Synonym_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "pattern a(v, _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", EXPRESSION_SPEC, "_\"x\"_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_PatternAssign_Underscore_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "pattern a(_, _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", UNDERSCORE, "_", EXPRESSION_SPEC, "_\"x\"_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_PatternAssign_IdentWithQuotes_ExpressionSpec_PartialMatch_SingleVariable_Valid)
        {
            string str = "pattern a(\"x\", _\"x\"_)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", IDENT_WITHQUOTES, "\"x\"", EXPRESSION_SPEC, "_\"x\"_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_PatternAssign_Underscore_Underscore_Valid)
        {
            string str = "pattern a(_, _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_PatternAssign_IdentWithQuotes_Underscore_Valid)
        {
            string str = "pattern a(\"x\", _)";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", IDENT_WITHQUOTES, "\"x\"", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }
    };
}