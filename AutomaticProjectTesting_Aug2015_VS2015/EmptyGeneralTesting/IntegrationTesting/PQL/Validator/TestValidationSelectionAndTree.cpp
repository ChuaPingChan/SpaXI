#include "CppUnitTest.h"
#include "string.h"
#include "..\PQLFriend\FriendSelectionValidator.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\Utility\UtilityQueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationSelectionAndTree)
    {
    public:
        string rawStr;
        string extracted;
        string actual;
        QueryTree *qtPtr;
        FriendSelectionValidator sdv = FriendSelectionValidator(qtPtr);

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            sdv = FriendSelectionValidator(qtPtr);
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

        TEST_METHOD(TestExtraction_Selection_SingleSynonym_SuchThatClause)
        {
            rawStr = "Select c such that Follows(1,2)";
            extracted = sdv.extractRawString(rawStr);
            actual = "Select c ";
            Assert::AreEqual(extracted, actual);
        }

        TEST_METHOD(TestExtraction_Selection_SingleSynonymAttribute_SuchThatClause)
        {
            rawStr = "Select c.procName such that Follows(1,2)";
            extracted = sdv.extractRawString(rawStr);
            actual = "Select c.procName ";
            Assert::AreEqual(extracted, actual);
        }

    };
}