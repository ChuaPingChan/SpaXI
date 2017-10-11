#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Attributeship.h"
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
        TEST_METHOD(TestValidity_With_ProcedureProcName_ProcedureProcName_DiffSynonym_StrStr_Valid)
        {
            string str = "p1.procName=p2.procName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p1");
            qt.insertSynonym(PROCEDURE, "p2");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROCEDURE_ATTRIBUTE, "p1", PROCEDURE_ATTRIBUTE, "p2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ProcedureProcName_SameSynonym_StrStr_Valid)
        {
            string str = "p.procName=p.procName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(qt));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_StmtStmtNum_StrInt_Invalid)
        {
            string str = "p.procName=s.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_AssignStmtNum_StrInt_Invalid)
        {
            string str = "p.procName=a.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(ASSIGN, "a");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_CallStmtNum_StrInt_Invalid)
        {
            string str = "p.procName=cl.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_CallProcNameStmt_StrStr_Valid)
        {
            string str = "p.procName=cl.procName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROCEDURE_ATTRIBUTE, "p", CALL_PROC_ATTRIBUTE, "cl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_WhileStmtNum_StrInt_Invalid)
        {
            string str = "p.procName=w.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(WHILE, "w");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_IfStmtNum_StrInt_Invalid)
        {
            string str = "p.procName=f.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(IF, "f");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_VariableVarName_StrStr_Valid)
        {
            string str = "p.procName=v.varName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROCEDURE_ATTRIBUTE, "p", VARIABLE_ATTRIBUTE, "v");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ConstantValue_StrInt_Invalid)
        {
            string str = "p.procName=c.value";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_Ident_StrStr_Valid)
        {
            string str = "p.procName=\"Pikachu\"";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROCEDURE_ATTRIBUTE, "p", IDENT_WITH_QUOTES_ATTRIBUTE, "Pikachu");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_Integer_StrInt_Invalid)
        {
            string str = "p.procName=12345";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProcedureProcName_ProgLine_StrInt_Invalid)
        {
            string str = "p.procName=pl";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ProcedureProcName_IntStr_Invalid)
        {
            string str = "s.stmt#=p.procName";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_StmtStmtNum_DiffSynonym_IntInt_Valid)
        {
            string str = "s1.stmt#=s2.stmt#";
            QueryTree qt;
            qt.insertSynonym(STMT, "s1");
            qt.insertSynonym(STMT, "s2");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STMT_ATTRIBUTE, "s1", STMT_ATTRIBUTE, "s2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_StmtStmtNum_SameSynonym_IntInt_Valid)
        {
            string str = "s.stmt#=s.stmt#";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(qt));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_VariableVarName_IntStr_Invalid)
        {
            string str = "s.stmt#=v.varName";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ConstantValue_IntInt_Valid)
        {
            string str = "s.stmt#=c.value";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            qt.insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STMT_ATTRIBUTE, "s", CONSTANT_ATTRIBUTE, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_IdentWithQuotes_IntStr_Invalid)
        {
            string str = "s.stmt#=\"Pikachu\"";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_Integer_IntInt_Valid)
        {
            string str = "s.stmt#=12345";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STMT_ATTRIBUTE, "s", INTEGER_ATTRIBUTE, "12345");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_StmtStmtNum_ProgLine_IntInt_Valid)
        {
            string str = "s.stmt#=pl";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(STMT_ATTRIBUTE, "s", PROG_LINE_ATTRIBUTE, "pl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ProcedureProcName_StrStr_Valid)
        {
            string str = "\"Pikachu\" = pokemon.procName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "pokemon");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(IDENT_WITH_QUOTES_ATTRIBUTE, "Pikachu", PROCEDURE_ATTRIBUTE, "pokemon");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_StmtStmtNum_StrInt_Invalid)
        {
            string str = "\"Pikachu\" = s.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "pokemon");
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_VariableVarName_StrStr_Valid)
        {
            string str = "\"Pikachu\" = v.varName";
            QueryTree qt;
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(IDENT_WITH_QUOTES_ATTRIBUTE, "Pikachu", VARIABLE_ATTRIBUTE, "v");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ConstantValue_StrInt_Invalid)
        {
            string str = "\"Pikachu\" = c.value";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "pokemon");
            qt.insertSynonym(CONSTANT, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_IdentWithQuotes_DiffIdent_StrStr_Valid)
        {
            string str = "\"RayYan\" = \"God\"";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(IDENT_WITH_QUOTES_ATTRIBUTE, "RayYan", IDENT_WITH_QUOTES_ATTRIBUTE, "God");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_IdentWithQuotes_SameIdent_StrStr_Valid)
        {
            string str = "\"Happiness\" = \"Happiness\"";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(qt));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_Integer_StrInt_Invalid)
        {
            string str = "\"Pikachu\" = 12345";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "pokemon");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_IdentWithQuotes_ProgLine_StrInt_Invalid)
        {
            string str = "\"Pikachu\" = pl";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "pokemon");
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_ProcedureProcNName_IntStr_Invalid)
        {
            string str = "12345=p.procName";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_StmtNum_IntInt_Valid)
        {
            string str = "12345 = s.stmt#";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_ATTRIBUTE, "12345", STMT_ATTRIBUTE, "s");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_Integer_VariableVarName_IntStr_Invalid)
        {
            string str = "12345=v.varName";
            QueryTree qt;
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_ConstantValue_IntInt_Valid)
        {
            string str = "12345 = c.value";
            QueryTree qt;
            qt.insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_ATTRIBUTE, "12345", CONSTANT_ATTRIBUTE, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_Integer_IdentQithQuotes_IntStr_Invalid)
        {
            string str = "12345 = \"Pikechu\"";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_Integer_DiffValue_IntInt_Invalid)
        {
            string str = "12345 = 67890";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Integer_Integer_SameValue_IntInt_Valid)
        {
            string str = "12345 = 12345";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(qt));
        }

        TEST_METHOD(TestValidity_With_Integer_ProgLine_IntInt_Valid)
        {
            string str = "12345 = pl";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(INTEGER_ATTRIBUTE, "12345", PROG_LINE_ATTRIBUTE, "pl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProcedureProcName_IntStr_Invalid)
        {
            string str = "pl = p.procName";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_CallStmtNum_IntInt_Valid)
        {
            string str = "pl = cl.stmt#";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            qt.insertSynonym(CALL, "cl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROG_LINE_ATTRIBUTE, "pl", CALL_STMT_ATTRIBUTE, "cl");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_VariableVarName_IntStr_Invalid)
        {
            string str = "pl = v.varName";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ConstantValue_IntInt_Valid)
        {
            string str = "pl = c.value";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            qt.insertSynonym(CONSTANT, "c");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROG_LINE_ATTRIBUTE, "pl", CONSTANT_ATTRIBUTE, "c");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_IdentWithQuotes_IntStr_Invalid)
        {
            string str = "pl = \"Pikachu\"";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_ProgLine_Integer_IntInt_Valid)
        {
            string str = "pl = 12";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROG_LINE_ATTRIBUTE, "pl", INTEGER_ATTRIBUTE, "12");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProgLine_DiffSynonym_IntInt_Valid)
        {
            string str = "pl1 = pl2";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl1");
            qt.insertSynonym(PROG_LINE, "pl2");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            WithClause expected = UtilitySelection::makeWithClause(PROG_LINE_ATTRIBUTE, "pl1", PROG_LINE_ATTRIBUTE, "pl2");
            WithClause actual = UtilitySelection::getFirstWithClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameWithClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_With_ProgLine_ProgLine_SameSynonym_IntInt_Valid)
        {
            string str = "pl = pl";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsTrue(wHandler.isValidWith(str));
            Assert::IsTrue(UtilityQueryTree::isEmptyWithClauseVectorInTree(qt));
        }

        TEST_METHOD(TestValidity_With_Mismatch_Synonym_AttrRef_Lhs_Invalid)
        {
            string str = "p.stmt# = 12345";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "p");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Mismatch_Synonym_AttrRef_Rhs_Invalid)
        {
            string str = "123 = v.value";
            QueryTree qt;
            qt.insertSynonym(VARIABLE, "v");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_Mismatch_ProgLine_AttrRef_Invalid)
        {
            string str = "pl.stmt# = 123";
            QueryTree qt;
            qt.insertSynonym(PROG_LINE, "pl");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_NonExistingAttrRef_Invalid)
        {
            string str = "s.line# = 123";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }

        TEST_METHOD(TestValidity_With_SynonymNotDeclared_Invalid)
        {
            string str = "s.stmt# = 123";
            QueryTree qt;
            WithHandler wHandler = WithHandler(&qt);
            Assert::IsFalse(wHandler.isValidWith(str));
        }
    };
}
