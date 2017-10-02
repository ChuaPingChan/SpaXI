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
            qt.insertVariable(ASSIGN, "a");
            qt.insertVariable(VARIABLE, "v");
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            PatternClause expected = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actual = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseContent(expected, actual));
        }
    };
}