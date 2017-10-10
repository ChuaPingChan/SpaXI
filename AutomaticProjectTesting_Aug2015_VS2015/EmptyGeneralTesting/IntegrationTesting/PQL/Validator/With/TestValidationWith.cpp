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
    };
}
