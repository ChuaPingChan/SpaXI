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

        TEST_METHOD(TestValidity_Declaration_Entity_SynonymSingle_Valid_Trial)
        {
            QueryTreeStub qtPtr;
            FriendDeclarationValidator fdv = FriendDeclarationValidator(&qtPtr);
            string str = "assign validEntityAndSynonym";
            Assert::IsTrue(fdv.isValidDeclaration(str));
            Assert::IsTrue(UtilityQueryTree::isGetAllAssignsSame(qtPtr, fdv.getQueryTreeCopy()));
        }

        /*TEST_METHOD(TestValidity_Declaration_Entity_SynonymMultiple_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Whitespace_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Newline_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_Entity_Synonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_SeparationBtwnArg_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(qvf.isValidDeclaration(str));
        }

        TEST_METHOD(TestValidity_Declaration_RepeatedSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "assign sameSynonym, sameSynonym, sameSynonym";
            Assert::IsFalse(qvf.isValidDeclaration(str));
        }*/

    };
}
