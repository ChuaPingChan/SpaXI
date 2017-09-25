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
            qvf.insertSynonymIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows*(1,_)";
            qvf.insertSynonymIntoQueryTree("int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,s)";
            qvf.insertSynonymIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,a)";
            qvf.insertSynonymIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,w)";
            qvf.insertSynonymIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Int_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,f)";
            qvf.insertSynonymIntoQueryTree("int", "1", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Int_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,pl)";
            qvf.insertSynonymIntoQueryTree("int", "1", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Int_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,cl)";
            qvf.insertSynonymIntoQueryTree("int", "1", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,3)";
            qvf.insertSynonymIntoQueryTree("int", "3");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,_)";
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,s)";
            qvf.insertSynonymIntoQueryTree("stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,a)";
            qvf.insertSynonymIntoQueryTree("assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,w)";
            qvf.insertSynonymIntoQueryTree("while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Underscore_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,f)";
            qvf.insertSynonymIntoQueryTree("if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Underscore_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,pl)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Underscore_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "FollowsSar(_,cl)";
            qvf.insertSynonymIntoQueryTree("call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,1)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,1)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,1)";
            qvf.insertSynonymIntoQueryTree("while", "w", "int", "1");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_If_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(f,1)";
            qvf.insertSynonymIntoQueryTree("if", "f", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_ProgLine_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(pl,1)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Call_int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(cl,1)";
            qvf.insertSynonymIntoQueryTree("call", "cl", "int", "1");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,_)";
            qvf.insertSynonymIntoQueryTree("stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,_)";
            qvf.insertSynonymIntoQueryTree("assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,_)";
            qvf.insertSynonymIntoQueryTree("while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_If_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(f,_)";
            qvf.insertSynonymIntoQueryTree("if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_ProgLine_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(pl,_)";
            qvf.insertSynonymIntoQueryTree("prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Call_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(cl,_)";
            qvf.insertSynonymIntoQueryTree("call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s1,s2)";
            qvf.insertSynonymIntoQueryTree("stmt", "s1", "stmt", "s2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,a)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Stmt_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,w)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Stmt_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,f)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement pl
        TEST_METHOD(TestValidity_FollowsStar_Stmt_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,pl)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Stmt_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,cl)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,s)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a1,a2)";
            qvf.insertSynonymIntoQueryTree("assign", "a1", "assign", "a2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Assign_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,w)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_Assign_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,f)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_Assign_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,pl)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_Assign_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(a,cl)";
            qvf.insertSynonymIntoQueryTree("assign", "a", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,s)";
            qvf.insertSynonymIntoQueryTree("while", "w", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,a)";
            qvf.insertSynonymIntoQueryTree("while", "w", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_While_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w1,w2)";
            qvf.insertSynonymIntoQueryTree("while", "w1", "while", "w2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement if
        TEST_METHOD(TestValidity_FollowsStar_While_If_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,f)";
            qvf.insertSynonymIntoQueryTree("while", "w", "if", "f");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement prog_line
        TEST_METHOD(TestValidity_FollowsStar_While_ProgLine_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,pl)";
            qvf.insertSynonymIntoQueryTree("while", "w", "prog_line", "pl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        //To change to IsTrue when implement call
        TEST_METHOD(TestValidity_FollowsStar_While_Call_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(w,c)";
            qvf.insertSynonymIntoQueryTree("while", "w", "call", "cl");
            Assert::IsFalse(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_SameSynonym_SameSynonym_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(s,s)";
            qvf.insertSynonymIntoQueryTree("stmt", "s", "stmt", "s");
            Assert::IsFalse(qvf.isValidFollows(str));
        }
    };
}
