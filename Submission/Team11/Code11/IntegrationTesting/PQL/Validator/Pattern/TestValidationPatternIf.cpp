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

        TEST_METHOD(TestValidity_Pattern_If_Variable_Underscore_Underscore_Valid)
        {
            str = "f(v, _, _)";
            qtPtr->insertSynonym(IF, "f");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(IF_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_Underscore_Underscore_Underscore_Valid)
        {
            str = "f(_, _, _)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(IF_PATTERN, "f", UNDERSCORE, "_", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_IdentWithQuotes_Underscore_Underscore_Valid)
        {
            str = "f(\"x\", _, _)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(IF_PATTERN, "f", IDENT_WITHQUOTES, "x", UNDERSCORE, "_", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseIfContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Pattern_If_FirstArg_NotVariable_Invalid)
        {
            str = "f(a, _, _)";
            qtPtr->insertSynonym(IF, "f");
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_If_SecondArg_NotUnderscore_Invalid)
        {
            str = "f(_, a, _)";
            qtPtr->insertSynonym(IF, "f");
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_If_ThirdArg_NotVUnderscore_Invalid)
        {
            str = "f(_, _, a)";
            qtPtr->insertSynonym(IF, "f");
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_TooLittleArguments_Invalid)
        {
            str = "f(_, _)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsFalse(pHandler.isValidPattern(str));
        }
    };
}
