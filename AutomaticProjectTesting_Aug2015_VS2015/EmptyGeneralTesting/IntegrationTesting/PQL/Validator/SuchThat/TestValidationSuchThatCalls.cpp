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
    TEST_CLASS(TestValidationSuchThat_Calls)
    {
    public:
        TEST_METHOD(TestValidity_SuchThat_Calls_Procedure_Procedure_Valid)
        {
            string str = "Calls(p, q)";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(PROCEDURE, "q");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, PROCEDURE, "p", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_Procedure_Underscore_Valid)
        {
            string str = "Calls(p, _)";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, PROCEDURE, "p", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_Underscore_Procedure_Valid)
        {
            string str = "Calls(_, q)";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "q");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, UNDERSCORE, "_", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_ProcName_Procedure_Valid)
        {
            string str = "Calls(\"First\", q)";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            qt.insertSynonym(PROCEDURE, "q");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, IDENT_WITHQUOTES, "First", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_Procedure_ProcName_Valid)
        {
            string str = "Calls(p, \"Second\")";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            qt.insertSynonym(PROCEDURE, "p");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, PROCEDURE, "p", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_ProcName_ProcName_Valid)
        {
            string str = "Calls(\"First\", \"Second\")";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, IDENT_WITHQUOTES, "First", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_Underscore_Underscore_Valid)
        {
            string str = "Calls(_,_)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_ProcName_Underscore_Valid)
        {
            string str = "Calls(\"First\",_)";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, IDENT_WITHQUOTES, "First", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_Underscore_ProcName_Valid)
        {
            string str = "Calls(_,\"Second\")";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLS, UNDERSCORE, "_", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /**********
        * Invalid *
        **********/
        TEST_METHOD(TestValidity_SuchThat_Calls_Procedure_Procedure_SameProc_Invalid)
        {
            string str = "Calls(p, p)";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_Calls_ProcName_ProcName_SameProcName_Invalid)
        {
            string str = "Calls(\"First\",\"First\" )";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\First\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }
    };
}
