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
    TEST_CLASS(TestValidationSuchThat_Next)
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

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Int_Valid)
        {
            str = "Next(1, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Underscore_Valid)
        {
            str = "Next(1, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Stmt_Valid)
        {
            str = "Next(1, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Assign_Valid)
        {
            str = "Next(1, a)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", ASSIGN, "a");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_While_Valid)
        {
            str = "Next(1, w)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_If_Valid)
        {
            str = "Next(1, f)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", IF, "f");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_ProgLine_Valid)
        {
            str = "Next(1, pl)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", PROG_LINE, "pl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Call_Valid)
        {
            str = "Next(1, cl)";
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, INTEGER, "1", CALL, "cl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Underscore_Int_Valid)
        {
            str = "Next(_, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, UNDERSCORE, "_", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Underscore_Underscore_Valid)
        {
            str = "Next(_, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Underscore_Synonym_Valid)
        {
            str = "Next(_, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, UNDERSCORE, "_", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Stmt_Int_Valid)
        {
            str = "Next(s, 2)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, STMT, "s", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Assign_Int_Valid)
        {
            str = "Next(a, 2)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, ASSIGN, "a", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_While_Int_Valid)
        {
            str = "Next(w, 2)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, WHILE, "w", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_If_Int_Valid)
        {
            str = "Next(f, 2)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, IF, "f", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_ProgLine_Int_Valid)
        {
            str = "Next(pl, 2)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, PROG_LINE, "pl", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Call_Int_Valid)
        {
            str = "Next(cl, 2)";
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, CALL, "cl", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Synonym_Underscore_Valid)
        {
            str = "Next(w, _)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, WHILE, "w", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Synonym_Synonym_Valid)
        {
            str = "Next(pl1, pl2)";
            qtPtr->insertSynonym(PROG_LINE, "pl1");
            qtPtr->insertSynonym(PROG_LINE, "pl2");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXT, PROG_LINE, "pl1", PROG_LINE, "pl2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }


        /**********
        * Invalid *
        **********/
        TEST_METHOD(TestValidity_SuchThat_Next_Int_Int_SameStmtNum_Invalid)
        {
            str = "Next(1, 1)";
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_Next_Int_Int_SameSynonymName_Invalid)
        {
            str = "Next(s, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }
    };
}
