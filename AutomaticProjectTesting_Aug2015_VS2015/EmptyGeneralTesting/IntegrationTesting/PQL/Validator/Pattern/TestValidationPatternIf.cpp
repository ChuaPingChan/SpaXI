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
* This class assumes that the overall pattern regex passed, hence only check for the If component
* The keyword, 'pattern', has been removed
*/

namespace UnitTesting
{
    TEST_CLASS(TestValidationPatternIf)
    {
    public:
        TEST_METHOD(TestValidity_Pattern_If_Variable_Underscore_Underscore_Valid)
        {
            string str = "f(v, _, _)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(If_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_Underscore_Underscore_Underscore_Valid)
        {
            string str = "f(_, _, _)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(If_PATTERN, "f", UNDERSCORE, "_", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_IdentWithQuotes_Underscore_Underscore_Valid)
        {
            string str = "f(\"x\", _, _)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(If_PATTERN, "f", IDENT_WITHQUOTES, "\"x\"", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_FirstArg_NotVariable_Invalid)
        {
            string str = "f(a, _, _)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_If_SecondArg_NotUnderscore_Invalid)
        {
            string str = "f(_, a, _)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_If_ThirdArg_NotVUnderscore_Invalid)
        {
            string str = "f(_, _, a)";
            QueryTree qt;
            qt.insertSynonym(IF, "f");
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}