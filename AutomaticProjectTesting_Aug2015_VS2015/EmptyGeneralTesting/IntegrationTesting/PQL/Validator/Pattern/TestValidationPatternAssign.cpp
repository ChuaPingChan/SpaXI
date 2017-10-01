#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Validator\Selection\Pattern\PatternHandler.h"
#include "..\SPA\PQL\Utilities\PatternClause.h"
//#include "..\..\Utility\UtilitySelection.h"

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
            PatternHandler pHandler = PatternHandler(&qt);
            Assert::IsTrue(pHandler.isValidPattern(str));
            //PatternClause expected = UtilitySelection::makePatternClause(0, 8, "1", 10, "\"x\"");
            //SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            //Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }
    };
}