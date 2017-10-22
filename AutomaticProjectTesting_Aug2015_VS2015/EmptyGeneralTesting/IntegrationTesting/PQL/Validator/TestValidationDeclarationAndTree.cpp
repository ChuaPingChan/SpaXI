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

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Stmt_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "stmt s";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("s");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllStmts(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Assign_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign a";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("a");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllAssigns(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_While_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "while w";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("w");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllWhiles(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_If_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "if f";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("f");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllIfs(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_ProgLine_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "prog_line pl";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("pl");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllProgLines(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Call_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "call cl";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("cl");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllCalls(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Procedure_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "procedure p";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("p");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllProcedures(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Variable_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "variable v";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("v");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllVariables(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymMultiple_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("validEntity");
            expectedList.insert("multipleVa1idSynonym");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllStmts(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Whitespace_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("validEntitySynonymWithWhitespace");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllVariables(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Newline_Valid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            unordered_set<string> expectedList;
            expectedList.insert("validEntitySynonymWithNewline");
            Assert::IsTrue(UtilityQueryTree::isSameContentAllWhiles(expectedList, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Invalid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_SeparationBtwnArg_Invalid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_RepeatedSynonym_Invalid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign sameSynonym, sameSynonym, sameSynonym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_ValidEntityConcatenateValidSynonym_Invalid)
        {
            QueryTree qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "stmts";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

    };
}
