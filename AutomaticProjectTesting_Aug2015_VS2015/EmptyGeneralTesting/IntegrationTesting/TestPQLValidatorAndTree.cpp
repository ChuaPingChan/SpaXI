#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/QueryValidator.h"

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
            QueryValidator qv;
            string str;

            str = "assign a; variable v; stmt s; while w; constant c; prog_line pl;";
            vector<string> tokenizer = qv.tokenizeTest(str);
            for (int i = 0; i < tokenizer.size(); i++)
            {
                bool testDeclaration = qv.isValidDeclarationTest(tokenizer.at(i));
                Assert::IsTrue(testDeclaration);
            }

            Assert::IsTrue(qtInstance->varExists("a"));
            Assert::IsTrue(qtInstance->varExists("v"));
            Assert::IsTrue(qtInstance->varExists("s"));
            Assert::IsTrue(qtInstance->varExists("w"));
            Assert::IsTrue(qtInstance->varExists("c"));
            Assert::IsTrue(qtInstance->varExists("pl"));

            Assert::IsTrue(qv.isArgumentInClauseTest("a", qtInstance->getAssigns()));
            Assert::IsTrue(qv.isArgumentInClauseTest("v", qtInstance->getVars()));
            Assert::IsTrue(qv.isArgumentInClauseTest("s", qtInstance->getStmts()));
            Assert::IsTrue(qv.isArgumentInClauseTest("w", qtInstance->getWhiles()));
            Assert::IsTrue(qv.isArgumentInClauseTest("c", qtInstance->getConsts()));
            Assert::IsTrue(qv.isArgumentInClauseTest("pl", qtInstance->getProgLines()));

            Assert::IsFalse(qv.isArgumentInClauseTest("a1", qtInstance->getAssigns()));
            Assert::IsFalse(qv.isArgumentInClauseTest("v1", qtInstance->getVars()));
            Assert::IsFalse(qv.isArgumentInClauseTest("s1", qtInstance->getStmts()));
            Assert::IsFalse(qv.isArgumentInClauseTest("w1", qtInstance->getWhiles()));
            Assert::IsFalse(qv.isArgumentInClauseTest("c1", qtInstance->getConsts()));
            Assert::IsFalse(qv.isArgumentInClauseTest("pl1", qtInstance->getProgLines()));



        }

        TEST_METHOD(TestQueryTreeSelect)
        {

            QueryValidator qv;
            string str;

            /*--------------- Select beginning --------------*/
            //Valid query
            qtInstance = qtInstance->clear();
			qv = QueryValidator();
            str = "Select v";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select s";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v";
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select 1";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select #";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v312";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qv.isValidSelectTest(str));


            /*--------------- Uses Clause --------------*/
            //Valid query
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(1,v)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(a,v)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(w,v)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(s,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(1,\"x\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(a,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(w,\"x\")";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(s,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(a,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(w,_)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(s,_)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select s such that Uses(1,s)";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(s,\"_x_\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Uses(v,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select w such that Uses(w,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select w such that Uses(_,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Modifies Clause --------------*/
            //Valid query
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(1,v)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(a,v)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(w,v)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(s,v)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(1,\"x\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(a,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(w,\"x\")";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(s,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(a,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(w,_)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(s,_)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select s such that Modifies(1,s)";
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Modifies(s,\"_x_\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select w such that Modifies(w,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select w such that Uses(_,\"_x_\")";
            qtInstance->insertVariable("while", "w");
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Follows/Follows* Clause --------------*/

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows*(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(x,y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(1,1)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(\"x\",y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Follows(\"x\",\"y\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Parent/Parent* Clause --------------*/

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(1,2)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(1,s)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(s,2)";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(s1,s2)";
            qtInstance->insertVariable("stmt", "s1");
            qtInstance->insertVariable("stmt", "s2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(1,w)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(w,2)";
            qtInstance->insertVariable("while", "w");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(w1,w2)";
            qtInstance->insertVariable("while", "w1");
            qtInstance->insertVariable("while", "w2");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(1,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent*(_,_)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid queries
            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(x,y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(a,4)";
            qtInstance->insertVariable("variable", "v");
            qtInstance->insertVariable("assign", "a");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(\"x\",y)";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select v such that Parent(\"x\",\"y\")";
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));


            /*--------------- Pattern Clause --------------*/

            //Valid Queries

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a pattern a(v,_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(v,_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(v,_\"1\"_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(_,_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(\"y\",_\"x\"_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(\"y\",_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(_,_)";
            qtInstance->insertVariable("assign", "a");
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid Queries

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a pattern a(s,\"x\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("stmt", "s");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(v,\"x+y\")";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select s  pattern s(v,\"x\")";
            qtInstance->insertVariable("stmt", "s");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(\"x+y\",_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(\"123\",_)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("variable", "v");
            Assert::IsFalse(qv.isValidSelectTest(str));

            qtInstance = qtInstance->clear(); qv = QueryValidator();
            str = "Select a  pattern a(_,a1)";
            qtInstance->insertVariable("assign", "a");
            qtInstance->insertVariable("assign", "a1");
            Assert::IsFalse(qv.isValidSelectTest(str));

        }
    };
}