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
            qvf.insertSynonymIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Parent(1,_)";
            qvf.insertSynonymIntoQueryTree("int", "1");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,s)";
            qvf.insertSynonymIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,a)";
            qvf.insertSynonymIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,w)";
            qvf.insertSynonymIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Int_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,f)";
            qvf.insertSynonymIntoQueryTree("int", "1", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_Int_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,pl)";
            qvf.insertSynonymIntoQueryTree("int", "1", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Int_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(1,cl)";
            qvf.insertSynonymIntoQueryTree("int", "1", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,3)";
            qvf.insertSynonymIntoQueryTree("int", "3");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,_)";
            Assert::IsTrue(qvf.isValidParent(str));
        }
        TEST_METHOD(TestValidity_Parent_Underscore_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,s)";
            qvf.insertSynonymIntoQueryTree("stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,a)";
            qvf.insertSynonymIntoQueryTree("assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Underscore_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,w)";
            qvf.insertSynonymIntoQueryTree("while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Underscore_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,f)";
            qvf.insertSynonymIntoQueryTree("if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_Underscore_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,pl)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Underscore_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(_,cl)";
            qvf.insertSynonymIntoQueryTree("call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,1)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "int", "1");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_int_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,1)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,1)";
            qvf.insertSynonymIntoQueryTree("while", "w", "int", "1");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_If_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(f,1)";
            qvf.insertSynonymIntoQueryTree("if", "f", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_ProgLine_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(pl,1)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Call_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(cl,1)";
            qvf.insertSynonymIntoQueryTree("call", "cl", "int", "1");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,_)";
            qvf.insertSynonymIntoQueryTree("stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Underscore_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,_)";
            qvf.insertSynonymIntoQueryTree("assign", "a");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,_)";
            qvf.insertSynonymIntoQueryTree("while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_If_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(f,_)";
            qvf.insertSynonymIntoQueryTree("if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_ProgLine_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(pl,_)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Call_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(cl,_)";
            qvf.insertSynonymIntoQueryTree("call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s1,s2)";
            qvf.insertSynonymIntoQueryTree("stmt", "s1", "stmt", "s2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,a)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Stmt_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,w)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "while", "w");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_Stmt_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,f)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement pl
        TEST_METHOD(TestValidity_Parent_Stmt_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,pl)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_Stmt_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,cl)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Stmt_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,s)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "stmt", "s");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Assign_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a1,a2)";
            qvf.insertSynonymIntoQueryTree("assign", "a1", "assign", "a2");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_While_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,w)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "while", "w");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_If_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,f)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_ProgLine_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,pl)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_Assign_Call_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(a,cl)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,s)";
            qvf.insertSynonymIntoQueryTree("while", "w", "stmt", "s");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,a)";
            qvf.insertSynonymIntoQueryTree("while", "w", "assign", "a");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_While_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w1,w2)";
            qvf.insertSynonymIntoQueryTree("while", "w1", "while", "w2");
            Assert::IsTrue(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_Parent_While_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,f)";
            qvf.insertSynonymIntoQueryTree("while", "w", "if", "f");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_Parent_While_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,pl)";
            qvf.insertSynonymIntoQueryTree("while", "w", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_Parent_While_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(w,c)";
            qvf.insertSynonymIntoQueryTree("while", "w", "call", "cl");
            Assert::IsFalse(qvf.isValidParent(str));
        }

        TEST_METHOD(TestValidity_Parent_SameSynonym_SameSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(s,s)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "stmt", "s");
            Assert::IsFalse(qvf.isValidParent(str));
        }
        
    };
}
