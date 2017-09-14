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
        QueryTree qt;
        TEST_METHOD(TestQueryTreeDeclaration)
        {
            QueryValidator qv;
            string str;

            qv = QueryValidator();   
            str = "assign a; variable v; stmt s; while w; constant c; prog_line pl;";
            vector<string> tokenizer = qv.tokenizerTest(str);
            for (int i = 0; i < tokenizer.size(); i++)
            {
                bool testDeclaration = qv.isValidDeclarationTest(tokenizer.at(i));
                Assert::IsTrue(testDeclaration);
            }

            qt = qv.qt;
            Assert::IsTrue(qt.varExists("a"));
            Assert::IsTrue(qt.varExists("v"));
            Assert::IsTrue(qt.varExists("s"));
            Assert::IsTrue(qt.varExists("w"));
            Assert::IsTrue(qt.varExists("c"));
            Assert::IsTrue(qt.varExists("pl"));

            Assert::IsTrue(qv.isArgumentInClauseTest("a",qt.getAssigns()));
            Assert::IsTrue(qv.isArgumentInClauseTest("v", qt.getVars()));
            Assert::IsTrue(qv.isArgumentInClauseTest("s", qt.getStmts()));
            Assert::IsTrue(qv.isArgumentInClauseTest("w", qt.getWhiles()));
            Assert::IsTrue(qv.isArgumentInClauseTest("c", qt.getConsts()));
            Assert::IsTrue(qv.isArgumentInClauseTest("pl", qt.getProgLines()));   

            Assert::IsFalse(qv.isArgumentInClauseTest("a1", qt.getAssigns()));
            Assert::IsFalse(qv.isArgumentInClauseTest("v1", qt.getVars()));
            Assert::IsFalse(qv.isArgumentInClauseTest("s1", qt.getStmts()));
            Assert::IsFalse(qv.isArgumentInClauseTest("w1", qt.getWhiles()));
            Assert::IsFalse(qv.isArgumentInClauseTest("c1", qt.getConsts()));
            Assert::IsFalse(qv.isArgumentInClauseTest("pl1", qt.getProgLines()));



        }

        TEST_METHOD(TestQueryTreeSelect)
        {
            
            QueryValidator qv;
            string str;

            /*--------------- Uses Clause --------------*/
            //Valid query
            qv = QueryValidator();
            str = "Select v such that Uses(1,v)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);         
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(a,v)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(w,v)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(s,v)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(1,\"x\")";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(a,\"x\")";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(w,\"x\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(s,\"x\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(1,_)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(a,_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(w,_)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(s,_)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qv = QueryValidator();
            str = "Select s such that Uses(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(s,\"_x_\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Uses(v,v)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select w such that Uses(w,\"_x_\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select w such that Uses(_,\"_x_\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Modifies Clause --------------*/
            //Valid query
            qv = QueryValidator();
            str = "Select v such that Modifies(1,v)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(a,v)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(w,v)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(s,v)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(1,\"x\")";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(a,\"x\")";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(w,\"x\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(s,\"x\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(1,_)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(a,_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(w,_)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(s,_)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qv = QueryValidator();
            str = "Select s such that Modifies(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Modifies(s,\"_x_\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select w such that Modifies(w,\"_x_\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select w such that Uses(_,\"_x_\")";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Follows/Follows* Clause --------------*/

            qv = QueryValidator();
            str = "Select v such that Follows(1,2)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(s,2)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(s1,s2)";
            qv.qt.insertVariable("stmt", "s1");
            qv.qt.insertVariable("stmt", "s2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(1,w)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(w,2)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(w1,w2)";
            qv.qt.insertVariable("while", "w1");
            qv.qt.insertVariable("while", "w2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(1,2)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(s,2)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(s1,s2)";
            qv.qt.insertVariable("stmt", "s1");
            qv.qt.insertVariable("stmt", "s2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(1,w)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(w,2)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(w1,w2)";
            qv.qt.insertVariable("while", "w1");
            qv.qt.insertVariable("while", "w2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows*(1,_)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid query
            qv = QueryValidator();
            str = "Select v such that Follows(x,y)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(1,1)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(\"x\",y)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Follows(\"x\",\"y\")";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            /*--------------- Parent/Parent* Clause --------------*/

            qv = QueryValidator();
            str = "Select v such that Parent(1,2)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(s,2)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(s1,s2)";
            qv.qt.insertVariable("stmt", "s1");
            qv.qt.insertVariable("stmt", "s2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(1,w)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(w,2)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(w1,w2)";
            qv.qt.insertVariable("while", "w1");
            qv.qt.insertVariable("while", "w2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(1,2)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(s,2)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(s1,s2)";
            qv.qt.insertVariable("stmt", "s1");
            qv.qt.insertVariable("stmt", "s2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(1,w)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(w,2)";
            qv.qt.insertVariable("while", "w");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(w1,w2)";
            qv.qt.insertVariable("while", "w1");
            qv.qt.insertVariable("while", "w2");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(1,_)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent*(_,_)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid queries
            qv = QueryValidator();
            str = "Select v such that Parent(x,y)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(a,4)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(\"x\",y)";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select v such that Parent(\"x\",\"y\")";
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));


            /*--------------- Pattern Clause --------------*/

            //Valid Queries

            qv = QueryValidator();
            str = "Select a pattern a(v,_\"x\"_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(v,_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(v,_\"1\"_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(_,_\"x\"_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(\"y\",_\"x\"_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(\"y\",_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(_,_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            //Invalid Queries

            qv = QueryValidator();
            str = "Select a pattern a(s,\"x\")";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(v,\"x+y\")";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select s  pattern s(v,\"x\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(\"x+y\",_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(\"123\",_)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("variable", "v");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select a  pattern a(_,a1)";
            qv.qt.insertVariable("assign", "a");
            qv.qt.insertVariable("assign", "a1");
            qv.qt.insertSelect(str);
            Assert::IsFalse(qv.isValidSelectTest(str));

        }
    };
}