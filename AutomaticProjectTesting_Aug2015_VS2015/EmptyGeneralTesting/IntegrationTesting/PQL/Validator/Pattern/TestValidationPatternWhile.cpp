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
* This class assumes that the overall pattern regex passed, hence only check for the while component
* The keyword, 'pattern', has been removed
*/

namespace UnitTesting
{
    TEST_CLASS(TestValidationPatternWhile)
    {
    public:
        TEST_METHOD(TestValidity_Pattern_While_Synonym_Underscore_Valid)
        {
            string str = "w(v, _)";
            QueryTree qt;
            qt.insertSynonym(WHILE, "w");
            qt.insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Underscore_Valid)
        {
            string str = "w(_, _)";
            QueryTree qt;
            qt.insertSynonym(WHILE, "w");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_IdentWithQuotes_Underscore_Valid)
        {
            string str = "w(\"x\", _)";
            QueryTree qt;
            qt.insertSynonym(WHILE, "w");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", IDENT_WITHQUOTES, "\"x\"", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_FirstArg_NotVariable_Invalid)
        {
            string str = "w(a, _)";
            QueryTree qt;
            qt.insertSynonym(WHILE, "w");
            qt.insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}
