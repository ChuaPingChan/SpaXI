#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\Entity.h"
#include "..\SPA\PQL\Relationship.h"
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
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", IDENT_WITHQUOTES, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Underscore_Valid)
        {
            string str = "Modifies(1, _)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Variable_Valid)
        {
            string str = "Modifies(1, v)";
            QueryTree qt;
            qt.insertVariable(VARIABLE, "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_IdentWithQuotes_Valid)
        {
            string str = "Modifies(a, \"x\")";
            QueryTree qt;
            qt.insertVariable(ASSIGN, "a");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, ASSIGN, "a", IDENT_WITHQUOTES, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Underscore_Valid)
        {
            string str = "Modifies(s, _)";
            QueryTree qt;
            qt.insertVariable(STMT, "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Variable_Valid)
        {
            string str = "Modifies(w, v)";
            QueryTree qt;
            qt.insertVariable(WHILE, "w");
            qt.insertVariable(VARIABLE, "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, WHILE, "w", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /******************************************************************************************/
        //TODO: Add test when procedure is inplemented [-- HERE --- ]
        /******************************************************************************************/


    };
}
