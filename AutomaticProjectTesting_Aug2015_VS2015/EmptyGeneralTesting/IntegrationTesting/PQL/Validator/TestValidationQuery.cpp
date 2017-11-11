#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\Entity.h"
#include "..\PQLFriend\FriendQueryValidator.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationQuery)
    {
    public:
        string query;
        QueryTree *qtPtr;
        FriendQueryValidator friendValidator = FriendQueryValidator(qtPtr);

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            friendValidator = FriendQueryValidator(qtPtr);
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

		/**********************
		* Empty Select Clause *
		***********************/
		TEST_METHOD(TestValidity_Query_NoSelect_ValidDeclaration_EmptySelection_Invalid)
		{
			query.append("stmt s;");
			query.append("  ");
			qtPtr->insertSynonym(STMT, "s");
			Assert::IsFalse(friendValidator.isValidQuery(query));
			Assert::IsTrue(friendValidator.getValidDeclarationFlag());
			Assert::IsFalse(friendValidator.getValidSelectionFlag());
		}

        /**************************
        * Select Clause - BOOLEAN *
        **************************/
        TEST_METHOD(TestValidity_Query_SelectBoolean_ValidDeclaration_ExpectTrue_Valid)
        {
            query.append("stmt s;");
            query.append("Select BOOLEAN");
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }


        TEST_METHOD(TestValidity_Query_SelectBoolean_InvalidDeclaration_ExpectFalse_Invalid)
        {
            query.append("statement s;");
            query.append("Select BOOLEAN");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_ExtraSemiColon_InvalidDeclaration_ExpectFalse_Invalid)
        {
            query.append("stmt s;;;;;;;;");
            query.append("Select BOOLEAN");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }
		

        TEST_METHOD(TestValidity_Query_SelectBoolean_NoDeclaration_Valid)
        {
            query.append("Select BOOLEAN");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_NoDeclaration_RubbishInFrontOfSelectBoolean_Invalid)
        {
            query.append("Rubbish Select BOOLEAN");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_NoDeclaration_InvalidClauses_Invalid)
        {
            query.append("Select BOOLEAN such that Bag(1, 2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_SuchThat_Valid)
        {
            query.append("if RayYan;");
            query.append("call AllGods;");
            query.append("Select BOOLEAN such that Parent*(RayYan, AllGods)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(PARENTSTAR, IF, "RayYan", CALL, "AllGods");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        /*********************************
        * Select Clause - Boolean - With *
        *********************************/
        TEST_METHOD(TestValidation_Query_SelectBoolean_With_Procedure_Call)
        {
            query.append("procedure p;");
            query.append("call c;");
            query.append("Select BOOLEAN with p.procName = c.procName");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));

            WithClause expectedWc = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", CALL, "c");
            WithClause actualWc = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expectedWc, actualWc));
        }

        
        /*********************************
        * Select Clause - Single Synonym *
        *********************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_Valid)
        {
            query.append("stmt s;");
            query.append("Select s");
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_StmtList_Valid)
        {
            query.append("stmtLst sl;");
            query.append("Select sl");
            qtPtr->insertSynonym(STMTLIST, "sl");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMTLIST, "sl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Select_Valid)
        {
            query.append("stmt Select;");
            query.append("Select Select");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "Select");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Modifies_Valid)
        {
            query.append("assign Modifies;");
            query.append("Select Modifies");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "Modifies");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_assign_Valid)
        {
            query.append("assign assign;");
            query.append("Select assign");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "assign");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_if_Valid)
        {
            query.append("if ifs;");
            query.append("Select ifs");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, IF, "ifs");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SameEntity_DuplicatedSynonym_Invalid)
        {
            query.append("assign a, a;");
            query.append("Select a");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_DiffEntity_DuplicatedSynonym_Invalid)
        {
            query.append("assign a, a1;");
            query.append("while a;");
            query.append("Select a");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        /************************************************
        * Select Clause - Single Synonym with Attribute *
        *************************************************/

        TEST_METHOD(TestValidity_Query_SelectAttributeOfCall_ValidDeclaration_ProcName_ExpectTrue_Valid)
        {
            query.append("call c;");
            query.append("Select c.procName");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "c");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            Assert::IsTrue(qtPtr->getSelectClause().isAttributeProcName);
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfCall_ValidDeclaration_StmtNum_ExpectTrue_Valid)
        {
            query.append("call c;");
            query.append("Select c.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "c");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            Assert::IsFalse(qtPtr->getSelectClause().isAttributeProcName);

        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfCall_ValidDeclaration_Value_ExpectFalse_Invalid)
        {
            query.append("call c;");
            query.append("Select c.value");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "c");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            Assert::IsFalse(qtPtr->getSelectClause().isAttributeProcName);

        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfStmt_ValidDeclaration_StmtNum_ExpectTrue_Valid)
        {
            query.append("stmt s;");
            query.append("Select s.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfStmt_ValidDeclaration_Value_ExpectFalse_Invalid)
        {
            query.append("stmt s;");
            query.append("Select s.value");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfAssign_ValidDeclaration_StmtNum_ExpectTrue_Valid)
        {
            query.append("assign a;");
            query.append("Select a.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfAssign_ValidDeclaration_VarName_ExpectFalse_Invalid)
        {
            query.append("assign a;");
            query.append("Select a.varName");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfAssign_ValidDeclaration_Value_ExpectFalse_Invalid)
        {
            query.append("assign a;");
            query.append("Select a.value");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfWhile_ValidDeclaration_StmtNum_ExpectTrue_Valid)
        {
            query.append("while w;");
            query.append("Select w.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, WHILE, "w");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfWhile_ValidDeclaration_VarName_ExpectFalse_Invalid)
        {
            query.append("while w;");
            query.append("Select w.varName");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, WHILE, "w");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfWhile_ValidDeclaration_Value_ExpectFalse_Invalid)
        {
            query.append("while w;");
            query.append("Select w.value");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, WHILE, "w");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfIf_ValidDeclaration_StmtNum_ExpectTrue_Valid)
        {
            query.append("if i;");
            query.append("Select i.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, IF, "i");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfIf_ValidDeclaration_VarName_ExpectFalse_Invalid)
        {
            query.append("if i;");
            query.append("Select i.varName");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, IF, "i");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfIf_ValidDeclaration_Value_ExpectFalse_Invalid)
        {
            query.append("if i;");
            query.append("Select i.value");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, IF, "i");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfVar_ValidDeclaration_VarName_ExpectTrue_Valid)
        {
            query.append("variable v;");
            query.append("Select v.varName");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, VARIABLE, "v");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfVar_ValidDeclaration_StmtNum_ExpectFalse_Invalid)
        {
            query.append("variable v;");
            query.append("Select v.stmt#");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, VARIABLE, "v");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfConstant_ValidDeclaration_Value_ExpectTrue_Valid)
        {
            query.append("constant c;");
            query.append("Select c.value");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CONSTANT, "c");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfConstant_ValidDeclaration_StmtNum_ExpectFalse_Invalid)
        {
            query.append("constant c;");
            query.append("Select c.stmt#");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CONSTANT, "c");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectAttributeOfProgLine_ValidDeclaration_StmtNum_ExpectFalse_Invalid)
        {
            query.append("prog_line pl;");
            query.append("Select pl.stmt#");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROG_LINE, "pl");
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }


        /*************************
        * Select Clause - Tuple *
        **************************/


        TEST_METHOD(TestValidity_Query_SelectTuple_OneSynonym_Valid)
        {
            query.append("assign a;");
            query.append("Select <a> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN };
            vector<string> synonymList = { "a" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 1);
            Assert::IsFalse(flagsForCall.front());
        }

        TEST_METHOD(TestValidity_Query_SelectTuple_TwoSynonyms_Valid)
        {
            query.append("assign a1, a2;");
            query.append("Select <a1,a2> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, ASSIGN };
            vector<string> synonymList = { "a1", "a2" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 2);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));

        }

        TEST_METHOD(TestValidity_Query_SelectTuple_TwoDifferentSynonyms_Valid)
        {
            query.append("assign a; stmt s;");
            query.append("Select <a, s> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT };
            vector<string> synonymList = { "a", "s" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 2);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
        }

        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleSynonyms_Valid)
        {
            query.append("assign a; stmt s; if i; while w; constant c;");
            query.append("Select <a, s, i, w, c>");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CONSTANT };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsFalse(flagsForCall.at(4));
        }


        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleDifferentSynonyms_WithSpaces_Valid)
        {
            query.append("assign a; stmt s; if i; while w; constant c;");
            query.append("Select <a,      s,       i,     w,        c> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CONSTANT };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsFalse(flagsForCall.at(4));
        }

        TEST_METHOD(TestValidity_Query_SelectTuple_SingleInvalidSynonym_Invalid)
        {
            query.append("assign a;");
            query.append("Select <a,> ");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN };
            vector<string> synonymList = { "a" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleInvalidSynonym_Invalid)
        {
            query.append("assign a; stmt s;");
            query.append("Select <a, s invalid character> ");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT};
            vector<string> synonymList = { "a", "s" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        /***************************************
        * Select Clause - Tuple With Attributes*
        ****************************************/
        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_OneSynonym_Valid)
        {
            query.append("assign a;");
            query.append("Select <a.stmt#> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN };
            vector<string> synonymList = { "a" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 1);
            Assert::IsFalse(flagsForCall.at(0));
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_TwoSynonyms_Valid)
        {
            query.append("assign a1, a2;");
            query.append("Select <a1,a2.stmt#> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, ASSIGN };
            vector<string> synonymList = { "a1", "a2" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 2);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_TwoDifferentSynonyms_Valid)
        {
            query.append("assign a; stmt s;");
            query.append("Select <a.stmt#, s.stmt#> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT };
            vector<string> synonymList = { "a", "s" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 2);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));

        }

        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleSynonyms_CallProcName_Valid)
        {
            query.append("assign a; stmt s; if i; while w; call c;");
            query.append("Select <a, s, i, w, c.procName>");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CALL };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsTrue(flagsForCall.at(4));
        }


        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleSynonyms_CallProcName_Invalid)
        {
            query.append("assign a; stmt s; if i; while w; call c;");
            query.append("Select <a, s, i, w, c.stmt#>");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CALL };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsFalse(flagsForCall.at(4));
        }


        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_MultipleSynonyms_Valid)
        {
            query.append("assign a; stmt s; if i; while w; constant c;");
            query.append("Select <a, s, i.stmt#, w, c.value>");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CONSTANT };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsFalse(flagsForCall.at(4));
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_MultipleAttributes_SameSynonym_Valid)
        {
            query.append("call c;");
            query.append("Select <c.stmt#,c.procName>");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { CALL, CALL };
            vector<string> synonymList = { "c","c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 2);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsTrue(flagsForCall.at(1));
            
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_MultipleDifferentSynonyms_WithSpaces_Valid)
        {
            query.append("assign a; stmt s; if i; while w; constant c;");
            query.append("Select <a,      s.stmt#,       i,     w,        c> ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CONSTANT };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.size() == 5);
            Assert::IsFalse(flagsForCall.at(0));
            Assert::IsFalse(flagsForCall.at(1));
            Assert::IsFalse(flagsForCall.at(2));
            Assert::IsFalse(flagsForCall.at(3));
            Assert::IsFalse(flagsForCall.at(4));
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_SingleInvalidSynonym_Invalid)
        {
            query.append("assign a;");
            query.append("Select <a.varName> ");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN };
            vector<string> synonymList = { "a" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.empty());
        }

        TEST_METHOD(TestValidity_Query_SelectTupleAttribute_MultipleInvalidSynonym_Invalid)
        {
            query.append("assign a; stmt s;");
            query.append("Select <a, s.value> ");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT };
            vector<string> synonymList = { "a", "s" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsFalse(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<bool> flagsForCall = qtPtr->getSelectClause().isAttributeProcNameForTuple;
            Assert::IsTrue(flagsForCall.empty());
        }


        /********************************************
        * Select Clause - Single Synonym - SuchThat *
        ********************************************/

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SingleSuchThat_Relation_Valid)
        {
            query.append("stmt s;");
            query.append("variable v;");
            query.append("Select s such that Modifies(s, v)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", VARIABLE, "v");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SingleSuchThat_Whitespace_Valid)
        {
            query.append("assign a;");
            query.append("while w;");
            query.append("   Select    a    such that    Follows*      (   a   ,   w   )  ");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_Relation_BeforeAndAfter_AndKeyword_Valid)
        {
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2) and Parent(w, s2)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENT, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }
        
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_AndKeyword_StickToPreviousRelation_Valid)
        {
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2)and Parent(w, s2)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENT, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_SuchThat_Relation_SuchThat_Relation_And_Relation_SuchThat_Relation_Valid)
        {
            query.append("stmt s1, s2, s3;");
            query.append("while w;");
            query.append("variable v, v2;");
            query.append("Select w such that Follows*(s1, s2) such that Parent*(w, s2) and Modifies(s1, v) such that Uses(w, v2) and Follows(s1, s3)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, WHILE, "w");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", VARIABLE, "v"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(USES, WHILE, "w", VARIABLE, "v2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s3"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }

        /*---------Extra miscellaneous such that test cases----------*/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Modifies_Procedure_Variable_Valid)
        {
            query.append("procedure Charizard;");
            query.append("variable Ash;");
            query.append("Select Charizard such that Modifies(Charizard, Ash)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "Charizard");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Charizard", VARIABLE, "Ash");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Modifies_IdentWQ_Variable_Valid)
        {
            query.append("variable Masterball;");
            query.append("Select Masterball such that Modifies(\"MewTwo\", Masterball)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, VARIABLE, "Masterball");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "MewTwo", VARIABLE, "Masterball");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Uses_IdentWQ_Variable_Valid)
        {
            query.append("procedure Pokemon;");
            query.append("Select Pokemon such that Uses(\"Azelf\", \"Psychic\")");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "Pokemon");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(USES, IDENT_WITHQUOTES, "Azelf", IDENT_WITHQUOTES, "Psychic");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_SingleSuchThat_FollowsStar_Assign_While_Valid)
        {
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such that Follows*(a, w)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_MultipleSuchThat_FollowsStar_SuchThat_ParentStar_Valid)
        {
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows*(s1, s2) such that Parent*(w, s2)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_Calls_Procedure_Variable_And_Modifies_Procedure_Variable_Valid)
        {
            query.append("procedure p;");
            query.append("procedure q;");
            query.append("variable v;");
            query.append("Select p such that Calls(p, q) and Modifies(p, v)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(CALLS, PROCEDURE, "p", PROCEDURE, "q"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "p", VARIABLE, "v"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SuchThat_Modifies_and_Uses_and_NextStar_Valid)
        {
            query.append("if if;");
            query.append("call c;");
            query.append("variable v;");
            query.append("Select c such that Modifies(if,v) and Uses(c, v) and Next*(if, c)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "c");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, IF, "if", VARIABLE, "v"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(USES, CALL, "c", VARIABLE, "v"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(NEXTSTAR, IF, "if", CALL, "c"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, *qtPtr));
        }


        /*******************************************
        * Select Clause - Single Synonym - Pattern *
        *******************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SinglePattern_Valid)
        {
            query.append("assign a;");
            query.append("variable v;");
            query.append("Select a pattern a(v, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            PatternClause expectedPc = UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actualPc = UtilitySelection::getFirstPatternClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expectedPc, actualPc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SinglePattern_DeformedExpression_Invalid)
        {
            query.append("assign a;");
            query.append("variable v;");
            query.append("Select a pattern a(v, \"1 2 + 3 + x\")");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Type_BeforeAndAfter_AndKeyword_Valid)
        {
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _) and a2(_,_)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_AndKeyword_StickToPreviousType_Valid)
        {
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _)and a2(_,_)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Pattern_AfterAndKeyword_Valid)
        {
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _) and a2(_,_) pattern a1 (v, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, *qtPtr));
        }


        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Pattern_Assign_And_While_And_If_Valid)
        {
            query.append("assign a;");
            query.append("variable v;");
            query.append("while w;");
            query.append("if f;");
            query.append("Select a pattern a(v, _) and w(_,_) and f(v, _ , _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(IF_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, *qtPtr));
        }

        /*---------Extra miscellaneous pattern test cases----------*/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_Pattern_Assign_And_While_Valid)
        {
            query.append("assign a;");
            query.append("variable v;");
            query.append("while w;");
            query.append("Select a pattern a(v, _) and w(_,_)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_Pattern_If_AsFirstClause_Valid)
        {
            query.append("call cl;");
            query.append("variable v;");
            query.append("if f;");
            query.append("Select cl pattern f (v, _, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "cl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListPc.push_back(UtilitySelection::makePatternClause(IF_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, *qtPtr));
        }

        /****************************************
        * Select Clause - Single Synonym - With *
        ****************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SingleWith_StrStr_Valid)
        {
            query.append("procedure p;");
            query.append("Select p with p.procName = \"Pikachu\"");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expectedSelect = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expectedSelect, qtPtr->getSelectClause()));
            WithClause expectedWith = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", IDENT_WITHQUOTES, "Pikachu");
            WithClause actualWith = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expectedWith, actualWith));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleWith_With_And_Valid)
        {
            query.append("procedure p;");
            query.append("stmt s;");
            query.append("constant c;");
            query.append("Select p with p.procName = \"Pikachu\" and c.value = s.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expectedSelect = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expectedSelect, qtPtr->getSelectClause()));
            vector<WithClause> expectedListWc;
            expectedListWc.push_back(UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", IDENT_WITHQUOTES, "Pikachu"));
            expectedListWc.push_back(UtilitySelection::makeWithClause(INTEGER_WITH, CONSTANT, "c", STMT, "s"));
            Assert::IsTrue(UtilitySelection::areSameWithClausesContentAsInTree(expectedListWc, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleWith_With_After_With_Valid)
        {
            query.append("procedure p;");
            query.append("if f;");
            query.append("while w;");
            query.append("Select p with p.procName = \"Pikachu\" with w.stmt# = f.stmt#");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expectedSelect = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expectedSelect, qtPtr->getSelectClause()));
            vector<WithClause> expectedListWc;
            expectedListWc.push_back(UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", IDENT_WITHQUOTES, "Pikachu"));
            expectedListWc.push_back(UtilitySelection::makeWithClause(INTEGER_WITH, WHILE, "w", IF, "f"));
            Assert::IsTrue(UtilitySelection::areSameWithClausesContentAsInTree(expectedListWc, *qtPtr));
        }


        /********************************************************
        * Select Clause - Single Synonym - SuchThat and Pattern *
        ********************************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_SuchThat_Parent_Pattern_Assign_And_Assign_SuchThat_Follows_And_Modifies_Pattern_Assign_Valid)
        {
            query.append("stmt s1, s2;");
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select s2 such that Parent(s1, s2) pattern a1(v, _) and a2(_,_) such that Follows(s2, s1) and Modifies(s1, \"x\") pattern a1 (v, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENT, STMT, "s1", STMT, "s2"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s2", STMT, "s1"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", IDENT_WITHQUOTES, "x"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_Parent_Pattern_Assign_And_While_SuchThat_Follows_And_Modifies_Pattern_Valid)
        {
            query.append("stmt s1, s2;");
            query.append("assign a1, a2;");
            query.append("while w1, w2;");
            query.append("variable v1, v2;");
            query.append("Select s2 such that Parent(s1, s2) pattern a1(v2, _) and w1(\"y\",_) such that Follows(s2, s1) and Modifies(s1, \"x\") pattern w2 (v1, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENT, STMT, "s1", STMT, "s2"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v2", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w1", IDENT_WITHQUOTES, "y", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s2", STMT, "s1"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", IDENT_WITHQUOTES, "x"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w2", VARIABLE, "v1", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Call_Pattern_Assign_SuchThat_FollowsStar_And_ParentStar_SuchThat_Modifies_Pattern_Assign_Pattern_Assign_Valid)
        {
            query.append("call cl;");
            query.append("stmt s1, s2, s3;");
            query.append("variable v;");
            query.append("assign a1, a2;");
            query.append("Select cl pattern a1(v, _) such that Follows*(s1, s2) and Parent*(s2, s3) such that Modifies(1, v) pattern a2(_, _) pattern a2(v, _)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "cl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, STMT, "s2", STMT, "s3"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", VARIABLE, "v"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSIGN_PATTERN, "a2", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, *qtPtr));
        }


        /*****************************************************
        * Select Clause - Single Synonym - SuchThat and With *
        *****************************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_With_SurroundedBy_SuchThat_Valid)
        {
            query.append("call cl;");
            query.append("stmt s1, s2, s3;");
            query.append("Select cl such that Follows*(s1, s2) with cl.stmt# = s3.stmt# such that Parent(s1, s3)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expectedSelect = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "cl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expectedSelect, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            vector<WithClause> expectedListWc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedListWc.push_back(UtilitySelection::makeWithClause(INTEGER_WITH, CALL, "cl", STMT, "s3"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENT, STMT, "s1", STMT, "s3"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
            Assert::IsTrue(UtilitySelection::areSameWithClausesContentAsInTree(expectedListWc, *qtPtr));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SuchThat_SurroundedBy_With_Valid)
        {
            query.append("variable v;");
            query.append("procedure p;");
            query.append("Select p with p.procName = v.varName such that Modifies(p, v) with v.varName = \"Pokeball\"");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            SelectClause expectedSelect = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expectedSelect, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<WithClause> expectedListWc;
            expectedListWc.push_back(UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", VARIABLE, "v"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "p", VARIABLE, "v"));
            expectedListWc.push_back(UtilitySelection::makeWithClause(STRING_WITH, VARIABLE, "v", IDENT_WITHQUOTES, "Pokeball"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
            Assert::IsTrue(UtilitySelection::areSameWithClausesContentAsInTree(expectedListWc, *qtPtr));
        }


        /***********************************
        * Select Clause - Tuple - SuchThat *
        ***********************************/
        TEST_METHOD(TestValidity_Query_SelectTuple_MultipleDifferentSynonyms_SuchThat_Valid)
        {
            query.append("assign a; stmt s; if i; while w; constant c;");
            query.append("Select <a,s,i,w,c> such that Follows(w,i)");
            Assert::IsTrue(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsTrue(friendValidator.getValidSelectionFlag());
            vector<Entity> entityList = { ASSIGN, STMT, IF, WHILE, CONSTANT };
            vector<string> synonymList = { "a", "s", "i", "w", "c" };
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_TUPLE, entityList, synonymList);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, WHILE, "w", IF, "i"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, *qtPtr));
        }

        /******************
        * Invalid Queries *
        ******************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_NonDeclaredSynonym_Invalid)
        {
            query.append("stmt s;");
            query.append("Select a");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SuchThatKeyword_ImmediatelyAfter_Select_Invalid)
        {
            query.append("stmt s;");
            query.append("Select such that Follows(1, 2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_patternKeyword_ImmediatelyAfter_Select_Invalid)
        {
            query.append("assign a;");
            query.append("Select pattern  a(_, _)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_withKeyword_ImmediatelyAfter_Select_Invalid)
        {
            query.append("constant c;");
            query.append("Select with c.value=1");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_Selection_Before_Declaration_Invalid)
        {
            query.append("Select s such that Modifies(s, v);");
            query.append("stmt s;");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsFalse(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_SingleSuchThat_Modifies_SecondArgInt_Invalid)
        {
            query.append("stmt s;");
            query.append("Select s such that Modifies(s, 12)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_FollowsStar_Whitespace_StarNotConnectedToKeyword_Invalid)
        {
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such that Follows    *      (a,w)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_WhitespaceWithinKeyword_Invalid)
        {
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such            that Follows(a,w)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Keyword_And_Missing_Invalid)
        {
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2) Parent(w, s2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Follows_Int_Int_SecondArg_GreaterThan_FirstArg_Invalid)
        {
            query.append("stmt s;");
            query.append("Select s such that Follows(15, 2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Parent_Int_Int_SecondArg_GreaterThan_FirstArg_Invalid)
        {
            query.append("stmt s;");
            query.append("Select s such that Parent(15, 2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_KeywordsBackToBack_Invalid)
        {
            query.append("stmt s;");
            query.append("Select s such thatParent(1, 2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Relation_And_Pattern_Type_And_SuchThat_Relation_Invalid)
        {
            query.append("stmt s;");
            query.append("variable v;");
            query.append("while w;");
            query.append("assign a1, a2;");
            query.append("Select s such that Modifies(1, v) and pattern a1(_, _) and such that Parent(w, a2)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Modifies_And_Assign_Invalid)
        {
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s such that Modifies(1, v) and a(_, _)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_Pattern_Assign_And_Modifies_Invalid)
        {
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s pattern a(_, _) and Modifies(1, v)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Assign_Invalid)
        {
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s such that a(v, _)");
            Assert::IsFalse(friendValidator.isValidQuery(query));
            Assert::IsTrue(friendValidator.getValidDeclarationFlag());
            Assert::IsFalse(friendValidator.getValidSelectionFlag());
        }

    };
}
