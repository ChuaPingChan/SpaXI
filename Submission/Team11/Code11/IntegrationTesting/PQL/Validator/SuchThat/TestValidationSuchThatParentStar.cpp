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
    TEST_CLASS(TestValidationSuchThat_ParentStarStar)
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

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Int_Valid)
        {
            str = "Parent*(1, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Underscore_Valid)
        {
            str = "Parent*(1, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Stmt_Valid)
        {
            str = "Parent*(1, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Assign_Valid)
        {
            str = "Parent*(1, a)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", ASSIGN, "a");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_While_Valid)
        {
            str = "Parent*(1, w)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_If_Valid)
        {
            str = "Parent*(1, f)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", IF, "f");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_ProgLine_Valid)
        {
            str = "Parent*(1, pl)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", PROG_LINE, "pl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Call_Valid)
        {
            str = "Parent*(1, cl)";
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", CALL, "cl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Underscore_Int_Valid)
        {
            str = "Parent*(_, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Underscore_Underscore_Valid)
        {
            str = "Parent*(_, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Underscore_Synonym_Valid)
        {
            str = "Parent*(_, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Stmt_Int_Valid)
        {
            str = "Parent*(s, 2)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, STMT, "s", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_While_Int_Valid)
        {
            str = "Parent*(w, 2)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_If_Int_Valid)
        {
            str = "Parent*(f, 2)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, IF, "f", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_ProgLine_Int_Valid)
        {
            str = "Parent*(pl, 2)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, PROG_LINE, "pl", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Call_Int_Invalid)
        {
            str = "Parent*(cl, 2)";
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Assign_Int_Invalid)
        {
            str = "Parent*(a, 2)";
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Synonym_Underscore_Valid)
        {
            str = "Parent*(w, _)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Synonym_Synonym_Valid)
        {
            str = "Parent*(w1, w2)";
            qtPtr->insertSynonym(WHILE, "w1");
            qtPtr->insertSynonym(WHILE, "w2");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w1", WHILE, "w2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }


        /**********
        * Invalid *
        **********/
        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Int_SameStmtNum_Invalid)
        {
            str = "Parent*(1, 1)";
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThat_ParentStar_Int_Int_SameSynonymName_Invalid)
        {
            str = "Parent*(s, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }
    };
}
