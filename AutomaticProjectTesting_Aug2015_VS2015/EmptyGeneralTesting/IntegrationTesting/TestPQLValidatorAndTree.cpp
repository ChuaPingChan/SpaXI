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

        }

        TEST_METHOD(TestQueryTreeSelect)
        {
            
            QueryValidator qv;
            string str;

            qv = QueryValidator();
            str = "Select s such that Uses(1,s)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);         
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select s such that Uses(s,_)";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));

            qv = QueryValidator();
            str = "Select s such that Uses(s,\"x\")";
            qv.qt.insertVariable("stmt", "s");
            qv.qt.insertSelect(str);
            Assert::IsTrue(qv.isValidSelectTest(str));


        }
    };
}