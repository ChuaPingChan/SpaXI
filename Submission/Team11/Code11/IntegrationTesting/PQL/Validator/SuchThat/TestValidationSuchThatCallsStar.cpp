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
    TEST_CLASS(TestValidationSuchThat_CallsStar)
    {
    public:
        string str;
        QueryTree *qtPtr;
        SuchThatHandler stHandler = SuchThatHandler(qtPtr);

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            stHandler = SuchThatHandler(qtPtr);
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Procedure_Procedure_Valid)
        {
            str = "Calls*(p, q)";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(PROCEDURE, "q");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, PROCEDURE, "p", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Procedure_Underscore_Valid)
        {
            str = "Calls*(p, _)";
            qtPtr->insertSynonym(PROCEDURE, "p");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, PROCEDURE, "p", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Underscore_Procedure_Valid)
        {
            str = "Calls*(_, q)";
            qtPtr->insertSynonym(PROCEDURE, "q");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, UNDERSCORE, "_", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_ProcName_Procedure_Valid)
        {
            str = "Calls*(\"First\", q)";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            qtPtr->insertSynonym(PROCEDURE, "q");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, IDENT_WITHQUOTES, "First", PROCEDURE, "q");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Procedure_ProcName_Valid)
        {
            str = "Calls*(p, \"Second\")";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            qtPtr->insertSynonym(PROCEDURE, "p");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, PROCEDURE, "p", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_ProcName_ProcName_Valid)
        {
            str = "Calls*(\"First\", \"Second\")";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, IDENT_WITHQUOTES, "First", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Underscore_Underscore_Valid)
        {
            str = "Calls*(_,_)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_ProcName_Underscore_Valid)
        {
            str = "Calls*(\"First\",_)";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"First\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, IDENT_WITHQUOTES, "First", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_Underscore_ProcName_Valid)
        {
            str = "Calls*(_,\"Second\")";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Second\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(CALLSSTAR, UNDERSCORE, "_", IDENT_WITHQUOTES, "Second");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /**********
        * Invalid *
        **********/
        TEST_METHOD(TestValidity_SuchThat_CallsStar_Procedure_Procedure_SameProc_Invalid)
        {
            str = "Calls*(p, p)";
            qtPtr->insertSynonym(PROCEDURE, "p");
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_CallsStar_ProcName_ProcName_SameProcName_Invalid)
        {
            str = "Calls*(\"First\",\"First\" )";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\First\"");
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }
    };
}
