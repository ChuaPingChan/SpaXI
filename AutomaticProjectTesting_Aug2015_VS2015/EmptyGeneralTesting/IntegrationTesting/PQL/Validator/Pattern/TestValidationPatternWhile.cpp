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
        QueryTree *qtPtr;
        string str;

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            str.clear();
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
            str.clear();
        }

        TEST_METHOD(TestValidity_Pattern_While_Synonym_Underscore_Valid)
        {
            str = "w(v, _)";
            qtPtr->insertSynonym(WHILE, "w");
            qtPtr->insertSynonym(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(qtPtr);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Underscore_Valid)
        {
            str = "w(_, _)";
            qtPtr->insertSynonym(WHILE, "w");
            PatternHandler pHandler = PatternHandler(qtPtr);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_IdentWithQuotes_Underscore_Valid)
        {
            str = "w(\"x\", _)";
            qtPtr->insertSynonym(WHILE, "w");
            PatternHandler pHandler = PatternHandler(qtPtr);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(WHILE_PATTERN, "w", IDENT_WITHQUOTES, "x", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_While_FirstArg_NotVariable_Invalid)
        {
            str = "w(a, _)";
            qtPtr->insertSynonym(WHILE, "w");
            qtPtr->insertSynonym(ASSIGN, "a");
            PatternHandler pHandler = PatternHandler(qtPtr);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_TooManyArguments_Invalid)
        {
            str = "w(_, _, _)";
            qtPtr->insertSynonym(WHILE, "w");
            PatternHandler pHandler = PatternHandler(qtPtr);
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}
