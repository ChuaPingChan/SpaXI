#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\Validator\Selection\SuchThat\SuchThatHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationSuchThatModifies)
    {
    public:

        TEST_METHOD(TestValidity_SuchThatModifies_Int_IdentWithQuotes_Valid)
        {
            string str = "Modifies(1, \"x\")";
            QueryTree qtPtr;
            SuchThatHandler stHandler = SuchThatHandler(&qtPtr);
            bool isValid = stHandler.isValidSuchThat(str);
            Assert::IsTrue(isValid);
            //Assert::IsTrue(UtilityQueryTree::isGetAllAssignsSame(qtPtr, fdv.getQueryTreeCopy()));
        }
    };
}
