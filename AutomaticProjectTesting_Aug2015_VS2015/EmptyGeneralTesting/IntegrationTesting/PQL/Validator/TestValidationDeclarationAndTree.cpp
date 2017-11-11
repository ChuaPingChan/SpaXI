#include "CppUnitTest.h"
#include "string.h"
#include "..\PQLFriend\FriendDeclarationValidator.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\Utility\UtilityQueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationDeclarationAndTree)
    {
    public:
        string str;
        QueryTree *qtPtr;
        FriendDeclarationValidator fdv = FriendDeclarationValidator(qtPtr);
        unordered_set<string> expectedList;

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            fdv = FriendDeclarationValidator(qtPtr);
            expectedList.clear();
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
            expectedList.clear();
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Stmt_Valid)
        {
            str = "stmt s";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("s");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllStmts(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Assign_Valid)
        {
            str = "assign a";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("a");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllAssigns(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_While_Valid)
        {
            str = "while w";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("w");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllWhiles(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_If_Valid)
        {
            str = "if f";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("f");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllIfs(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_ProgLine_Valid)
        {
            str = "prog_line pl";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("pl");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllProgLines(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Call_Valid)
        {
            str = "call cl";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("cl");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllCalls(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Procedure_Valid)
        {
            str = "procedure p";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("p");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllProcedures(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Variable_Valid)
        {
            str = "variable v";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("v");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllVariables(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymMultiple_Valid)
        {
            str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("validEntity");
            expectedList.insert("multipleVa1idSynonym");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllStmts(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Whitespace_Valid)
        {
            str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("validEntitySynonymWithWhitespace");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllVariables(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Newline_Valid)
        {
            str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("validEntitySynonymWithNewline");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllWhiles(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_MultipleNewline_Valid)
        {
            str = "while \n w1, w2\n, \n w3";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            expectedList.insert("w1");
            expectedList.insert("w2");
            expectedList.insert("w3");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllWhiles(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Invalid)
        {
            str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_SeparationBtwnArg_Invalid)
        {
            str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_RepeatedSynonym_Invalid)
        {
            str = "assign sameSynonym, sameSynonym, sameSynonym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_ValidEntityConcatenateValidSynonym_Invalid)
        {
            str = "stmts";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

    };
}
