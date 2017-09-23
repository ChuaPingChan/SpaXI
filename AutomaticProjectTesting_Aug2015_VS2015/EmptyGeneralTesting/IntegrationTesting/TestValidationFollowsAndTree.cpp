#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationFollowsAndTree)
    {
    public:
        TEST_METHOD(TestValidity_Follows_Int_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,2)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows(1,_)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,s)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,a)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,w)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_Int_If_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows(1,f)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "if", "f");
        Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_Int_ProgLine_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows(1,pl)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "prog_line", "pl");
        Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Int_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(1,cl)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,3)";
            qvf.insertTwoVarIntoQueryTree("_", "", "int", "3");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,_)";
            qvf.insertTwoVarIntoQueryTree("_", "", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }
        TEST_METHOD(TestValidity_Follows_Underscore_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,s)";
            qvf.insertTwoVarIntoQueryTree("_", "", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Underscore_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,a)";
            qvf.insertTwoVarIntoQueryTree("_", "", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Underscore_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,w)";
            qvf.insertTwoVarIntoQueryTree("_", "", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_Underscore_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,f)";
            qvf.insertTwoVarIntoQueryTree("_", "", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_Underscore_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,pl)";
            qvf.insertTwoVarIntoQueryTree("_", "", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Underscore_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,cl)";
            qvf.insertTwoVarIntoQueryTree("_", "", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Stmt_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,1)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Assign_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,1)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_While_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,1)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_If_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(f,1)";
            qvf.insertTwoVarIntoQueryTree("if", "f", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_ProgLine_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(pl,1)";
            qvf.insertTwoVarIntoQueryTree("prog_line", "pl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Call_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(cl,1)";
            qvf.insertTwoVarIntoQueryTree("call", "cl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Stmt_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,_)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Assign_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,_)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_While_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,_)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_If_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(f,_)";
            qvf.insertTwoVarIntoQueryTree("if", "f", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_ProgLine_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(pl,_)";
            qvf.insertTwoVarIntoQueryTree("prog_line", "pl", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Call_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(cl,_)";
            qvf.insertTwoVarIntoQueryTree("call", "cl", "_", "");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Stmt_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s1,s2)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s1", "stmt", "s2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Stmt_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,a)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Stmt_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,w)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_Stmt_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,f)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement pl
        TEST_METHOD(TestValidity_Follows_Stmt_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,pl)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Stmt_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,cl)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Assign_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,s)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Assign_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a1,a2)";
            qvf.insertTwoVarIntoQueryTree("assign", "a1", "assign", "a2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Assign_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,w)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_Assign_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,f)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_Assign_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,pl)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_Assign_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,cl)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_While_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,s)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_While_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,a)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_While_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w1,w2)";
            qvf.insertTwoVarIntoQueryTree("while", "w1", "while", "w2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Follows_While_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,f)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Follows_While_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,pl)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Follows_While_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(w,c)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_SameSynonym_SameSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(s,s)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "stmt", "s");
            Assert::IsFalse(qvf.isValidFollows(str));
        }
    
    };
}
