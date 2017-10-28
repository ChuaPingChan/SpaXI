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

        TEST_METHOD(TestExtraction_Selection_SingleSynonym_SuchThatClause)
        {
            QueryTree qtPtr;
            FriendSelectionValidator sdv = FriendSelectionValidator(&qtPtr);
            string rawStr = "Select c such that Follows(1,2)";
            string extracted = sdv.extractRawString(rawStr);
            string actual = "Select c ";
            Assert::AreEqual(extracted, actual);
        }

        TEST_METHOD(TestExtraction_Selection_SingleSynonymAttribute_SuchThatClause)
        {
            QueryTree qtPtr;
            FriendSelectionValidator sdv = FriendSelectionValidator(&qtPtr);
            string rawStr = "Select c.procName such that Follows(1,2)";
            string extracted = sdv.extractRawString(rawStr);
            string actual = "Select c.procName ";
            Assert::AreEqual(extracted, actual);
        }

    };
}