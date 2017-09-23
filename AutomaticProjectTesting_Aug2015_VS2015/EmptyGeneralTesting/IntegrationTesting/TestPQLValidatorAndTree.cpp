#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/QueryValidator.h"
#include "../SPA/PQL/QueryValidatorFriend.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
    TEST_CLASS(TestPQLValidatorAndTree)
    {
    public:
		QueryTree* qtInstance = QueryTree::getInstance();
        TEST_METHOD(TestQueryTreeDeclaration)
        {
			qtInstance = qtInstance->clear();
            //QueryValidator qv;
            QueryValidatorFriend qvf;
            string str;

            str = "assign a; variable v; stmt s; while w; constant c; prog_line pl;";
            vector<string> tokenizer = qvf.tokenize(str);
            for (int i = 0; i < tokenizer.size(); i++)
            {
                bool testDeclaration = qvf.isValidDeclaration(tokenizer.at(i));
                Assert::IsTrue(testDeclaration);
            }

            Assert::IsTrue(qtInstance->varExists("a"));
            Assert::IsTrue(qtInstance->varExists("v"));
            Assert::IsTrue(qtInstance->varExists("s"));
            Assert::IsTrue(qtInstance->varExists("w"));
            Assert::IsTrue(qtInstance->varExists("c"));
            Assert::IsTrue(qtInstance->varExists("pl"));

            Assert::IsTrue(qvf.isArgumentInClause("a", qtInstance->getAssigns()));
            Assert::IsTrue(qvf.isArgumentInClause("v", qtInstance->getVars()));
            Assert::IsTrue(qvf.isArgumentInClause("s", qtInstance->getStmts()));
            Assert::IsTrue(qvf.isArgumentInClause("w", qtInstance->getWhiles()));
            Assert::IsTrue(qvf.isArgumentInClause("c", qtInstance->getConsts()));
            Assert::IsTrue(qvf.isArgumentInClause("pl", qtInstance->getProgLines()));

            Assert::IsFalse(qvf.isArgumentInClause("a1", qtInstance->getAssigns()));
            Assert::IsFalse(qvf.isArgumentInClause("v1", qtInstance->getVars()));
            Assert::IsFalse(qvf.isArgumentInClause("s1", qtInstance->getStmts()));
            Assert::IsFalse(qvf.isArgumentInClause("w1", qtInstance->getWhiles()));
            Assert::IsFalse(qvf.isArgumentInClause("c1", qtInstance->getConsts()));
            Assert::IsFalse(qvf.isArgumentInClause("pl1", qtInstance->getProgLines()));



        }

        TEST_METHOD(TestQueryTreeSelect)
        {

            QueryValidatorFriend qvf;
            string str;

            /*--------------- Select beginning --------------*/
            //Valid query
            qtInstance = qtInstance->clear();
			qvf = QueryValidatorFriend();
            str = "Select v";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select s";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid query

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v";
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select 1";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select #";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v312";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qvf.isValidSelect(str));


            /*--------------- Uses Clause --------------*/
            //Valid query
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(1,v)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(a,v)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(w,v)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(s,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(1,\"x\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(a,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(w,\"x\")";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(s,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(a,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(w,_)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(s,_)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select s such that Uses(1,s)";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(s,\"_x_\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Uses(v,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select w such that Uses(w,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select w such that Uses(_,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qvf.isValidSelect(str));

            /*--------------- Modifies Clause --------------*/
            //Valid query
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(1,v)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(a,v)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(w,v)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(s,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(1,\"x\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(a,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(w,\"x\")";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(s,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(a,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(w,_)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(s,_)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select s such that Modifies(1,s)";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Modifies(s,\"_x_\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select w such that Modifies(w,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select w such that Uses(_,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qvf.isValidSelect(str));

            /*--------------- Follows/Follows* Clause --------------*/

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows*(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));


            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(_, _)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(x,y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(1,1)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(\"x\",y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Follows(\"x\",\"y\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            /*--------------- Parent/Parent* Clause --------------*/

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent*(_,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid queries
            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(x,y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(a,4)";
            qtInstance->insertVariable("variable", "v");
            qtInstance->insertVariable("assign", "a");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(\"x\",y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select v such that Parent(\"x\",\"y\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));


            /*--------------- Pattern Clause --------------*/

            //Valid Queries

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a pattern a(v,_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(v,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(v,_\"1\"_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(_,_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(\"y\",_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(\"y\",_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(_,_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qvf.isValidSelect(str));

            //Invalid Queries

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a pattern a(s,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(v,\"x+y\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select s  pattern s(v,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(\"x+y\",_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(\"123\",_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qvf.isValidSelect(str));

            qtInstance = qtInstance->clear(); qvf = QueryValidatorFriend();
            str = "Select a  pattern a(_,a1)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("assign", "a1");
            Assert::IsFalse(qvf.isValidSelect(str));

        }


        /****************************************
        * Such That Relationship Validity Tests *
        ****************************************/
        /*************** Test Modifies ***************/
        TEST_METHOD(TestModifies_Valid)
        {
            QueryValidatorFriend qvf;
            string str;

            //TODO: Test validity of modifies
        }

        /*************** Test Uses ***************/
        TEST_METHOD(TestUses_Valid)
        {
            QueryValidatorFriend qvf;
            string str;

            //TODO: Test validity of uses
        }

        /*************** Test Follows ***************/
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

        /*TEST_METHOD(TestValidity_Follows_Int_If_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows(1,f)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "if", "f");
        Assert::IsTrue(qvf.isValidFollows(str));
        }*/

        /*TEST_METHOD(TestValidity_Follows_Int_ProgLine_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows(1,pl)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "prog_line", "pl");
        Assert::IsTrue(qvf.isValidFollows(str));
        }*/

        TEST_METHOD(TestValidity_Follows_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,3)";
            qvf.insertTwoVarIntoQueryTree("_", "", "int", "3");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_Follows_Underscore_Underscore_Valid, qtInstance)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(_,_)";
            qvf.insertTwoVarIntoQueryTree("_", "", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        /*************** Test FollowsStar ***************/
        TEST_METHOD(TestValidity_FollowsStar_Int_Int_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows*(1,2)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "int", "2");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Underscore_Valid)
        {
            QueryValidatorFriend qvf = QueryValidatorFriend();;
            string str = "Follows*(1,_)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Stmt_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,s)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "stmt", "s");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_Assign_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,a)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "assign", "a");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Int_While_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(1,w)";
            qvf.insertTwoVarIntoQueryTree("int", "1", "while", "w");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        /*TEST_METHOD(TestValidity_FollowsStar_Int_If_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows*(1,f)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "if", "f");
        Assert::IsTrue(qvf.isValidFollows(str));
        }*/

        /*TEST_METHOD(TestValidity_FollowsStar_Int_ProgLine_Valid)
        {
        QueryValidatorFriend qvf;
        string str = "Follows*(1,pl)";
        qvf.insertTwoVarIntoQueryTree("int", "1", "prog_line", "pl");
        Assert::IsTrue(qvf.isValidFollows(str));
        }*/

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Int_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,3)";
            qvf.insertTwoVarIntoQueryTree("_", "", "int", "3");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        TEST_METHOD(TestValidity_FollowsStar_Underscore_Underscore_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(_,_)";
            qvf.insertTwoVarIntoQueryTree("_", "", "_", "");
            Assert::IsTrue(qvf.isValidFollows(str));
        }

        /*************** Test Parent ***************/
        TEST_METHOD(TestParent_Valid)
        {
            QueryValidatorFriend qvf;
            string str;

            //TODO: Test validity of parent
        }

        /*************** Test ParentStar ***************/
        TEST_METHOD(TestParentStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str;

            //TODO: Test validity of parentstar
        }

    };
}