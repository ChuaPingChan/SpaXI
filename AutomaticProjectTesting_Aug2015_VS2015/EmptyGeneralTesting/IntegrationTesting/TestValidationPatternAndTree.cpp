#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestValidationPatternAndTree)
    {
    public:
        /*********
        * Assign *
        *********/
        TEST_METHOD(TestValidity_Pattern_Assign_Variable_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v,_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "_", "");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Variable_Ident_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "_\"x\"_");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestValidity_Pattern_Assign_Variable_Ident_ExactMatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, \"x\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }
        
        //TODO: Change to IsTrue when implement expression
        TEST_METHOD(TestValidity_Pattern_Assign_Variable_Expression_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _\"x+3-y*2\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "_\"x+3-y*2\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestValidity_Pattern_Assign_Variable_Expression_Exactmatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, \"x+3-y*2\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "\"x+3-y*2\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Ident_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "_", "", "ident", "_\"x\"_");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement ExactMatch
        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Ident_ExactMatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, \"x\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "_", "", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement expression
        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Expression_Submatch_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "pattern a(_, _\"x+3-y*2\"_)";
        qvf.insertThreeParamIntoQueryTree("assign", "a", "_", "", "ident", "_\"x+3-y*2\"_");
        Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Expression_Exactmatch_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "pattern a(_, \"x+3-y*2\")";
        qvf.insertThreeParamIntoQueryTree("assign", "a", "_", "", "ident", "\"x+3-y*2\"");
        Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Ident_Ident_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"x\", _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "ident", "\"x\"", "ident", "_\"x\"_");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement ExactMatch
        TEST_METHOD(TestValidity_Pattern_Assign_Ident_Ident_ExactMatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"x\", \"x\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "ident", "\"x\"", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement eexpression
        TEST_METHOD(TestValidity_Pattern_Assign_Ident_Expression_Submatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"x\", _\"x+3-y*2\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "ident", "\"x\"", "ident", "_\"x+3-y*2\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implement exact match
        TEST_METHOD(TestValidity_Pattern_Assign_Ident_Expression_Exactmatch_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"x\", \"x+3-y*2\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "ident", "\"x\"", "ident", "\"x+3-y*2\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(_, _)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "_", "", "_", "");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_Ident_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(\"x\", _)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "ident", "\"x\"", "_", "");
            Assert::IsTrue(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IncomleteExpression_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, _\"-1\"_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "_\"-1\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_Assign_IncomleteExpression_ExactMatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v, \"-1\")";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "ident", "\"-1\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }


        /********
        * While *
        ********/
        //TODO: Change to IsTrue when implement while
        TEST_METHOD(TestValidity_Pattern_While_Variable_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(v,_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "var", "v", "_", "");
            Assert::IsFalse(qvf.isValidPattern(str));
        }
        
        //TODO: Change to IsTrue when implementing while
        TEST_METHOD(TestValidity_Pattern_While_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(_, _)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "_", "", "_", "");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        //TODO: Change to IsTrue when implementing while
        TEST_METHOD(TestValidity_Pattern_While_Ident_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(\"x\", _)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "ident", "\"x\"", "_", "");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Variable_Ident_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern while(v, _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "var", "v", "ident", "_\"x\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Variable_Ident_ExactMatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(v, \"x\")";
            qvf.insertThreeParamIntoQueryTree("while", "v", "var", "v", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Ident_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(_, _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "_", "", "ident", "_\"x\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Ident_ExactMatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(_, \"x\")";
            qvf.insertThreeParamIntoQueryTree("while", "w", "_", "", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Expression_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(_, _\"x+3-y*2\"_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "_", "", "ident", "_\"x+3-y*2\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Underscore_Expression_Exactmatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(_, \"x+3-y*2\")";
            qvf.insertThreeParamIntoQueryTree("while", "w", "_", "", "ident", "\"x+3-y*2\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Ident_Ident_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(\"x\", _\"x\"_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "ident", "\"x\"", "ident", "_\"x\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Ident_Ident_ExactMatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(\"x\", \"x\")";
            qvf.insertThreeParamIntoQueryTree("while", "w", "ident", "\"x\"", "ident", "\"x\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Ident_Expression_Submatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(\"x\", _\"x+3-y*2\"_)";
            qvf.insertThreeParamIntoQueryTree("while", "w", "ident", "\"x\"", "ident", "_\"x+3-y*2\"_");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_While_Ident_Expression_Exactmatch_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern w(\"x\", \"x+3-y*2\")";
            qvf.insertThreeParamIntoQueryTree("while", "w", "ident", "\"x\"", "ident", "\"x+3-y*2\"");
            Assert::IsFalse(qvf.isValidPattern(str));
        }


        /*****
        * If *
        *****/



        /******************
        * General Invalid *
        ******************/
        TEST_METHOD(TestValidity_Pattern_ArgOne_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern c(v,_)";
            qvf.insertThreeParamIntoQueryTree("call", "c", "var", "v", "_", "");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_ArgTwo_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(s,_)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "stmt", "s", "_", "");
            Assert::IsFalse(qvf.isValidPattern(str));
        }

        TEST_METHOD(TestValidity_Pattern_ArgThree_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "pattern a(v,s)";
            qvf.insertThreeParamIntoQueryTree("assign", "a", "var", "v", "stmt", "s");
            Assert::IsFalse(qvf.isValidPattern(str));
        }
       
    };
}
