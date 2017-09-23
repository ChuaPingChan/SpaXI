#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationModifiesAndTree)
    {
    public:
        TEST_METHOD(TestValidity_Modifies_Int_Ident_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Modifies(1,\"x\")";
            qvf.insertTwoVarIntoQueryTree("int", "1", "int", "\"x\"");
            Assert::IsTrue(qvf.isValidModifies(str));
        }
    };
}
