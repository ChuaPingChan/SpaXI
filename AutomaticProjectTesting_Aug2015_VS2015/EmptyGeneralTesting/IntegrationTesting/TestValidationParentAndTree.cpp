#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationParentAndTree)
    {
    public:
        TEST_METHOD(TestValidity_Parent_Int_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,2)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Parent(1,_)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "_", "");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,s)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,a)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,w)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Int_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,f)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_Int_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,pl)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Int_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,cl)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,3)";
            qvf.insertTwoVarIntoQueryTree("_", "", "int", "3");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,_)";
            qvf.insertTwoVarIntoQueryTree("_", "", "_", "");
            Assert::IsTrue(qvf.isValidParent(str));
        }
        TEST_METHOD(TestValidity_Parent_Underscore_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,s)";
            qvf.insertTwoVarIntoQueryTree("_", "", "stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,a)";
            qvf.insertTwoVarIntoQueryTree("_", "", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,w)";
            qvf.insertTwoVarIntoQueryTree("_", "", "while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Underscore_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,f)";
            qvf.insertTwoVarIntoQueryTree("_", "", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_Underscore_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,pl)";
            qvf.insertTwoVarIntoQueryTree("_", "", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Underscore_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,cl)";
            qvf.insertTwoVarIntoQueryTree("_", "", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,1)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "int", "1");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_int_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,1)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,1)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "int", "1");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_If_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(f,1)";
            qvf.insertTwoVarIntoQueryTree("if", "f", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_ProgLine_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(pl,1)";
            qvf.insertTwoVarIntoQueryTree("prog_line", "pl", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Call_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(cl,1)";
            qvf.insertTwoVarIntoQueryTree("call", "cl", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,_)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "_", "");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Underscore_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,_)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "_", "");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,_)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "_", "");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_If_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(f,_)";
            qvf.insertTwoVarIntoQueryTree("if", "f", "_", "");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_ProgLine_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(pl,_)";
            qvf.insertTwoVarIntoQueryTree("prog_line", "pl", "_", "");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Call_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(cl,_)";
            qvf.insertTwoVarIntoQueryTree("call", "cl", "_", "");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s1,s2)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s1", "stmt", "s2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,a)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,w)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Stmt_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,f)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement pl
        TEST_METHOD(TestValidity_Parent_Stmt_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,pl)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Stmt_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,cl)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Stmt_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,s)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "stmt", "s");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Assign_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a1,a2)";
            qvf.insertTwoVarIntoQueryTree("assign", "a1", "assign", "a2");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_While_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,w)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "while", "w");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_If_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,f)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_ProgLine_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,pl)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Call_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,cl)";
            qvf.insertTwoVarIntoQueryTree("assign", "a", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,s)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,a)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w1,w2)";
            qvf.insertTwoVarIntoQueryTree("while", "w1", "while", "w2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_While_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,f)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_While_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,pl)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_While_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,c)";
            qvf.insertTwoVarIntoQueryTree("while", "w", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_SameSynonym_SameSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,s)";
            qvf.insertTwoVarIntoQueryTree("stmt", "s", "stmt", "s");
            Assert::IsFalse(qvf.isValidParent(str));
        }
        
    };
}
