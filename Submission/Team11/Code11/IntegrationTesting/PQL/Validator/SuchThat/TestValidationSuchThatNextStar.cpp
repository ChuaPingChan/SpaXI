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
    TEST_CLASS(TestValidationSuchThat_NextStar)
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

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Int_Valid)
        {
            str = "Next*(1, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Underscore_Valid)
        {
            str = "Next*(1, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Stmt_Valid)
        {
            str = "Next*(1, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Assign_Valid)
        {
            str = "Next*(1, a)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", ASSIGN, "a");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_While_Valid)
        {
            str = "Next*(1, w)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_If_Valid)
        {
            str = "Next*(1, f)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", IF, "f");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_ProgLine_Valid)
        {
            str = "Next*(1, pl)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", PROG_LINE, "pl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Call_Valid)
        {
            str = "Next*(1, cl)";
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", CALL, "cl");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Underscore_Int_Valid)
        {
            str = "Next*(_, 2)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, UNDERSCORE, "_", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Underscore_Underscore_Valid)
        {
            str = "Next*(_, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, UNDERSCORE, "_", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Underscore_Synonym_Valid)
        {
            str = "Next*(_, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, UNDERSCORE, "_", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Stmt_Int_Valid)
        {
            str = "Next*(s, 2)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, STMT, "s", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Assign_Int_Valid)
        {
            str = "Next*(a, 2)";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, ASSIGN, "a", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_While_Int_Valid)
        {
            str = "Next*(w, 2)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, WHILE, "w", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_If_Int_Valid)
        {
            str = "Next*(f, 2)";
            qtPtr->insertSynonym(IF, "f");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, IF, "f", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_ProgLine_Int_Valid)
        {
            str = "Next*(pl, 2)";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, PROG_LINE, "pl", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Call_Int_Valid)
        {
            str = "Next*(cl, 2)";
            qtPtr->insertSynonym(CALL, "cl");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, CALL, "cl", INTEGER, "2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Synonym_Underscore_Valid)
        {
            str = "Next*(w, _)";
            qtPtr->insertSynonym(WHILE, "w");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, WHILE, "w", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Synonym_Synonym_Valid)
        {
            str = "Next*(w1, w2)";
            qtPtr->insertSynonym(WHILE, "w1");
            qtPtr->insertSynonym(WHILE, "w2");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, WHILE, "w1", WHILE, "w2");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Int_SameStmtNum_Valid)
        {
            str = "Next*(1, 1)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, INTEGER, "1", INTEGER, "1");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_NextStar_Int_Int_SameSynonymName_Valid)
        {
            str = "Next*(s, s)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(NEXTSTAR, STMT, "s", STMT, "s");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }
    };
}
