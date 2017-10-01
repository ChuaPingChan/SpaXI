#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Validator\Selection\SuchThat\SuchThatHandler.h"
#include "..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationSuchThatModifies)
    {
    public:
        TEST_METHOD(TestValidity_SuchThatModifies_Int_IdentWithQuotes_Valid)
        {
            string str = "Modifies(1, \"x\")";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 8, "1", 10, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Underscore_Valid)
        {
            string str = "Modifies(1, _)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 8, "1", 9, "_");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Variable_Valid)
        {
            string str = "Modifies(1, v)";
            QueryTree qt;
            qt.insertVariable("variable", "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 8, "1", 7, "v");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_IdentWithQuotes_Valid)
        {
            string str = "Modifies(a, \"x\")";
            QueryTree qt;
            qt.insertVariable("assign", "a");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 1, "a", 10, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Underscore_Valid)
        {
            string str = "Modifies(s, _)";
            QueryTree qt;
            qt.insertVariable("stmt", "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 0, "s", 9, "_");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Variable_Valid)
        {
            string str = "Modifies(w, v)";
            QueryTree qt;
            qt.insertVariable("while", "w");
            qt.insertVariable("variable", "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(0, 2, "w", 7, "v");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /******************************************************************************************/
        //TODO: Add test when procedure is inplemented [-- HERE --- ]
        /******************************************************************************************/


    };
}
