#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationUsesAndTree)
    {
    public:
        TEST_METHOD(TestValidity_Uses_Int_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(1,\"x\")";
            qvf.insertSynonymIntoQueryTree("int", "1");
            Assert::IsTrue(qvf.isValidUses(str));
        }
    };
}
