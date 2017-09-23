#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationFollowsStarAndTree)
    {
    public:
        TEST_METHOD(TestValidity_FollowsStar_Int_Int_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows*(1,2)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows*(1,_)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,s)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,a)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,w)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Int_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,f)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Int_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,pl)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Int_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,cl)";
            qvf.insertTwoParamIntoQueryTree("int", "1", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,3)";
            qvf.insertTwoParamIntoQueryTree("_", "", "int", "3");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,_)";
            qvf.insertTwoParamIntoQueryTree("_", "", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,s)";
            qvf.insertTwoParamIntoQueryTree("_", "", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,a)";
            qvf.insertTwoParamIntoQueryTree("_", "", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,w)";
            qvf.insertTwoParamIntoQueryTree("_", "", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Underscore_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,f)";
            qvf.insertTwoParamIntoQueryTree("_", "", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Underscore_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,pl)";
            qvf.insertTwoParamIntoQueryTree("_", "", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Underscore_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "FollowsSar(_,cl)";
            qvf.insertTwoParamIntoQueryTree("_", "", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,1)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,1)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,1)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_If_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(f,1)";
            qvf.insertTwoParamIntoQueryTree("if", "f", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_ProgLine_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(pl,1)";
            qvf.insertTwoParamIntoQueryTree("prog_line", "pl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Call_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(cl,1)";
            qvf.insertTwoParamIntoQueryTree("call", "cl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,_)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,_)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,_)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_If_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(f,_)";
            qvf.insertTwoParamIntoQueryTree("if", "f", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_ProgLine_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(pl,_)";
            qvf.insertTwoParamIntoQueryTree("prog_line", "pl", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Call_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(cl,_)";
            qvf.insertTwoParamIntoQueryTree("call", "cl", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s1,s2)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s1", "stmt", "s2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,a)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,w)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Stmt_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,f)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement pl
        TEST_METHOD(TestValidity_FollowsStar_Stmt_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,pl)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Stmt_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,cl)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,s)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a1,a2)";
            qvf.insertTwoParamIntoQueryTree("assign", "a1", "assign", "a2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,w)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Assign_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,f)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Assign_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,pl)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Assign_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,cl)";
            qvf.insertTwoParamIntoQueryTree("assign", "a", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,s)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,a)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w1,w2)";
            qvf.insertTwoParamIntoQueryTree("while", "w1", "while", "w2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_While_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,f)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_While_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,pl)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_While_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,c)";
            qvf.insertTwoParamIntoQueryTree("while", "w", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_SameSynonym_SameSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,s)";
            qvf.insertTwoParamIntoQueryTree("stmt", "s", "stmt", "s");
            Assert::IsFalse(qvf.isValidFollows(str));
        }
    };
}
