#include "CppUnitTest.h"
#include "string.h"
#include "PQLFriend\FriendDeclarationValidator.h"
#include "..\..\SPA\PQL\QueryTreeStub.h"
#include "Utility\UtilityQueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationDeclarationAndTree)
    {
    public:

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Valid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign validEntityAndSynonym";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            Assert::IsTrue(UtilityQueryTree::isGetAllAssignsSame(qtPtr, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymMultiple_Valid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            Assert::IsTrue(UtilityQueryTree::isGetAllStmtsSame(qtPtr, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Whitespace_Valid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            Assert::IsTrue(UtilityQueryTree::isGetAllVariablesSame(qtPtr, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Newline_Valid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            Assert::IsTrue(UtilityQueryTree::isGetAllWhilesSame(qtPtr, fdv.getQueryTreeCopy()));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Invalid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_SeparationBtwnArg_Invalid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_RepeatedSynonym_Invalid)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign sameSynonym, sameSynonym, sameSynonym";
            Assert::IsFalse(fdv.isValidDeclaration(str));
        }

    };
}
