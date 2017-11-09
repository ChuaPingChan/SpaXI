#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Withship.h"
#include "..\SPA\PQL\Validator\Selection\With\WithHandler.h"
#include "..\SPA\PQL\Utilities\WithClause.h"
#include "..\..\Utility\UtilitySelection.h"
#include "..\..\Utility\UtilityQueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/*
* This class assumes that the overall with regex passed, hence only check for the component
* The keyword, 'with', has been removed
*/

namespace UnitTesting
{
    TEST_CLASS(TestValidationWith)
    {
    public:
        QueryTree *qtPtr;
        string str;

        TEST_METHOD_INITIALIZE(Test_Initialisation) 
        {
            qtPtr = new QueryTree;
            str.clear();
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
            str.clear();
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ProcedureProcName_DiffSynonym_StrStr_Valid)
        {
            str = "p1.procName=p2.procName";
            qtPtr->insertSynonym(PROCEDURE, "p1");
            qtPtr->insertSynonym(PROCEDURE, "p2");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p1", PROCEDURE, "p2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ProcedureProcName_SameSynonym_StrStr_Valid)
        {
            str = "p.procName=p.procName";
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(*qtPtr));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_StmtStmtNum_StrInt_Invalid)
        {
            str = "p.procName=s.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_AssignStmtNum_StrInt_Invalid)
        {
            str = "p.procName=a.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(ASSIGN, "a");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_CallStmtNum_StrInt_Invalid)
        {
            str = "p.procName=cl.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_CallProcNameStmt_StrStr_Valid)
        {
            str = "p.procName=cl.procName";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", CALL, "cl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_WhileStmtNum_StrInt_Invalid)
        {
            str = "p.procName=w.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(WHILE, "w");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_IfStmtNum_StrInt_Invalid)
        {
            str = "p.procName=f.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(IF, "f");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_VariableVarName_StrStr_Valid)
        {
            str = "p.procName=v.varName";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", VARIABLE, "v");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ConstantValue_StrInt_Invalid)
        {
            str = "p.procName=c.value";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_Ident_StrStr_Valid)
        {
            str = "p.procName=\"Pikachu\"";
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, PROCEDURE, "p", IDENT_WITHQUOTES, "Pikachu");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_Integer_StrInt_Invalid)
        {
            str = "p.procName=12345";
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ProgLine_StrInt_Invalid)
        {
            str = "p.procName=pl";
            qtPtr->insertSynonym(PROCEDURE, "p");
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ProcedureProcName_IntStr_Invalid)
        {
            str = "s.stmt#=p.procName";
            qtPtr->insertSynonym(STMT, "s");
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_StmtStmtNum_DiffSynonym_IntInt_Valid)
        {
            str = "s1.stmt#=s2.stmt#";
            qtPtr->insertSynonym(STMT, "s1");
            qtPtr->insertSynonym(STMT, "s2");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, STMT, "s1", STMT, "s2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_StmtStmtNum_SameSynonym_IntInt_Valid)
        {
            str = "s.stmt#=s.stmt#";
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(*qtPtr));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_VariableVarName_IntStr_Invalid)
        {
            str = "s.stmt#=v.varName";
            qtPtr->insertSynonym(STMT, "s");
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ConstantValue_IntInt_Valid)
        {
            str = "s.stmt#=c.value";
            qtPtr->insertSynonym(STMT, "s");
            qtPtr->insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, STMT, "s", CONSTANT, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_IdentWithQuotes_IntStr_Invalid)
        {
            str = "s.stmt#=\"Pikachu\"";
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_Integer_IntInt_Valid)
        {
            str = "s.stmt#=12345";
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, STMT, "s", INTEGER, "12345");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ProgLine_IntInt_Valid)
        {
            str = "s.stmt#=pl";
            qtPtr->insertSynonym(STMT, "s");
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, STMT, "s", PROG_LINE, "pl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ProcedureProcName_StrStr_Valid)
        {
            str = "\"Pikachu\" = pokemon.procName";
            qtPtr->insertSynonym(PROCEDURE, "pokemon");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, IDENT_WITHQUOTES, "Pikachu", PROCEDURE, "pokemon");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_StmtStmtNum_StrInt_Invalid)
        {
            str = "\"Pikachu\" = s.stmt#";
            qtPtr->insertSynonym(PROCEDURE, "pokemon");
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_VariableVarName_StrStr_Valid)
        {
            str = "\"Pikachu\" = v.varName";
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STRING_WITH, IDENT_WITHQUOTES, "Pikachu", VARIABLE, "v");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ConstantValue_StrInt_Invalid)
        {
            str = "\"Pikachu\" = c.value";
            qtPtr->insertSynonym(PROCEDURE, "pokemon");
            qtPtr->insertSynonym(CONSTANT, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_IdentWithQuotes_DiffIdent_StrStr_Valid)
        {
            str = "\"Happy\" = \"Sad\"";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_IdentWithQuotes_SameIdent_StrStr_Valid)
        {
            str = "\"Happiness\" = \"Happiness\"";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(*qtPtr));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_Integer_StrInt_Invalid)
        {
            str = "\"Pikachu\" = 12345";
            qtPtr->insertSynonym(PROCEDURE, "pokemon");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ProgLine_StrInt_Invalid)
        {
            str = "\"Pikachu\" = pl";
            qtPtr->insertSynonym(PROCEDURE, "pokemon");
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_ProcedureProcNName_IntStr_Invalid)
        {
            str = "12345=p.procName";
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_StmtNum_IntInt_Valid)
        {
            str = "12345 = s.stmt#";
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, INTEGER, "12345", STMT, "s");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_Integer_VariableVarName_IntStr_Invalid)
        {
            str = "12345=v.varName";
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_ConstantValue_IntInt_Valid)
        {
            str = "12345 = c.value";
            qtPtr->insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, INTEGER, "12345", CONSTANT, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_Integer_IdentQithQuotes_IntStr_Invalid)
        {
            str = "12345 = \"Pikechu\"";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_Integer_DiffValue_IntInt_Invalid)
        {
            str = "12345 = 67890";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_Integer_SameValue_IntInt_Valid)
        {
            str = "12345 = 12345";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(*qtPtr));
        }

        TEST_METHOD(TestValidity_With_Integer_ProgLine_IntInt_Valid)
        {
            str = "12345 = pl";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, INTEGER, "12345", PROG_LINE, "pl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProcedureProcName_IntStr_Invalid)
        {
            str = "pl = p.procName";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_CallStmtNum_IntInt_Valid)
        {
            str = "pl = cl.stmt#";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            qtPtr->insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, PROG_LINE, "pl", CALL, "cl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_VariableVarName_IntStr_Invalid)
        {
            str = "pl = v.varName";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ConstantValue_IntInt_Valid)
        {
            str = "pl = c.value";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            qtPtr->insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, PROG_LINE, "pl", CONSTANT, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_IdentWithQuotes_IntStr_Invalid)
        {
            str = "pl = \"Pikachu\"";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_Integer_IntInt_Valid)
        {
            str = "pl = 12";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, PROG_LINE, "pl", INTEGER, "12");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProgLine_DiffSynonym_IntInt_Valid)
        {
            str = "pl1 = pl2";
            qtPtr->insertSynonym(PROG_LINE, "pl1");
            qtPtr->insertSynonym(PROG_LINE, "pl2");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_WITH, PROG_LINE, "pl1", PROG_LINE, "pl2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProgLine_SameSynonym_IntInt_Valid)
        {
            str = "pl = pl";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(*qtPtr));
        }

        TEST_METHOD(TestValidity_With_Mismatch_Synonym_AttrRef_Lhs_Invalid)
        {
            str = "p.stmt# = 12345";
            qtPtr->insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Mismatch_Synonym_AttrRef_Rhs_Invalid)
        {
            str = "123 = v.value";
            qtPtr->insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Mismatch_ProgLine_AttrRef_Invalid)
        {
            str = "pl.stmt# = 123";
            qtPtr->insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_NonExistingAttrRef_Invalid)
        {
            str = "s.line# = 123";
            qtPtr->insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_SynonymNotDeclared_Invalid)
        {
            str = "s.stmt# = 123";
            WithHandler wHandler = WithHandler(qtPtr);
            Assert::IsFalse(wHandler.isValidWith(str));
        }
    };
}
