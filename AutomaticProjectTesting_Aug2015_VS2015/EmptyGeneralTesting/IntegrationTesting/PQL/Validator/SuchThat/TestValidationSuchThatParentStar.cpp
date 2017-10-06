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
    TEST_CLASS(TestValidationSuchThatParentStarStar)
    {
    public:
        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Int_Valid)
        {
            string str = "Parent*(1, 2)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Underscore_Valid)
        {
            string str = "Parent*(1, _)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Stmt_Valid)
        {
            string str = "Parent*(1, s)";
            QueryTree qt;
            qt.insertVariable(STMT, "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Assign_Valid)
        {
            string str = "Parent*(1, a)";
            QueryTree qt;
            qt.insertVariable(ASSIGN, "a");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", ASSIGN, "a");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_While_Valid)
        {
            string str = "Parent*(1, w)";
            QueryTree qt;
            qt.insertVariable(WHILE, "w");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /*TEST_METHOD(TestValidity_SuchThatParentStar_Int_If_Valid)
        {
        string str = "Parent*(1, f)";
        QueryTree qt;
        qt.insertVariable(IF, "f");
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsTrue(stHandler.isValidSuchThat(str));
        SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", IF, "f");
        SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
        Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_ProgLine_Valid)
        {
        string str = "Parent*(1, pl)";
        QueryTree qt;
        qt.insertVariable(PROG_LINE, "pl");
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsTrue(stHandler.isValidSuchThat(str));
        SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", PROG_LINE, "pl");
        SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
        Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Call_Valid)
        {
        string str = "Parent*(1, cl)";
        QueryTree qt;
        qt.insertVariable(CALL, "cl");
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsTrue(stHandler.isValidSuchThat(str));
        SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, INTEGER, "1", CALL, "cl");
        SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
        Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }*/

        TEST_METHOD(TestValidity_SuchThatParentStar_Underscore_Int_Valid)
        {
            string str = "Parent*(_, 2)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Underscore_Underscore_Valid)
        {
            string str = "Parent*(_, _)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Underscore_Synonym_Valid)
        {
            string str = "Parent*(_, s)";
            QueryTree qt;
            qt.insertVariable(STMT, "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, UNDERSCORE, "_", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Stmt_Int_Valid)
        {
            string str = "Parent*(s, 2)";
            QueryTree qt;
            qt.insertVariable(STMT, "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, STMT, "s", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_While_Int_Valid)
        {
            string str = "Parent*(w, 2)";
            QueryTree qt;
            qt.insertVariable(WHILE, "w");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        /*TEST_METHOD(TestValidity_SuchThatParentStar_If_Int_Valid)
        {
        string str = "Parent*(f, 2)";
        QueryTree qt;
        qt.insertVariable(IF, "f");
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsTrue(stHandler.isValidSuchThat(str));
        SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, IF, "f", INTEGER, "2");
        SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
        Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_ProgLine_Int_Valid)
        {
        string str = "Parent*(pl, 2)";
        QueryTree qt;
        qt.insertVariable(PROG_LINE, "pl");
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsTrue(stHandler.isValidSuchThat(str));
        SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, PROG_LINE, "pl", INTEGER, "2");
        SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
        Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Call_Int_Invalid)
        {
        string str = "Parent*(cl, 2)";
        QueryTree qt;
        SuchThatHandler stHandler = SuchThatHandler(&qt);
        Assert::IsFalse(stHandler.isValidSuchThat(str));
        }*/

        TEST_METHOD(TestValidity_SuchThatParentStar_Assign_Int_Invalid)
        {
            string str = "Parent*(a, 2)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Synonym_Underscore_Valid)
        {
            string str = "Parent*(w, _)";
            QueryTree qt;
            qt.insertVariable(WHILE, "w");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Synonym_Synonym_Valid)
        {
            string str = "Parent*(w1, w2)";
            QueryTree qt;
            qt.insertVariable(WHILE, "w1");
            qt.insertVariable(WHILE, "w2");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w1", WHILE, "w2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }


        /**********
        * Invalid *
        **********/
        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Int_SameStmtNum_Invalid)
        {
            string str = "Parent*(1, 1)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }

        TEST_METHOD(TestValidity_SuchThatParentStar_Int_Int_SameSynonymName_Invalid)
        {
            string str = "Parent*(s, s)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsFalse(stHandler.isValidSuchThat(str));
        }
    };
}
