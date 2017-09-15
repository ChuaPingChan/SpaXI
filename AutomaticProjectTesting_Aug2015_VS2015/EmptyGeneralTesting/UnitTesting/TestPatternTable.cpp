#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SPA\PKB\PatternTable.h"
#include "..\SPA\PKB\PatternTable.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting {
    TEST_CLASS(TestPatternTable) 
    {
    public:
        TEST_METHOD(TestPopulate) {
            PatternTable pt;
            Assert::IsTrue(pt.addToPatternTable(1, "x","a+b-c+d"));
            Assert::IsTrue(pt.addToPatternTable(2, "y","a-b*c-d"));
            Assert::IsTrue(pt.addToPatternTable(3, "z","a+b*(c+d)-e"));
            Assert::IsTrue(pt.addToPatternTable(4, "hello","a"));
             

            // check that the function rejects duplicated values
            Assert::IsFalse(pt.addToPatternTable(1, "z", "a+b"));
            
            // postfix test
            Assert::IsTrue(pt.getExpression(1).second.compare("ab+c-d+") == 0);
            Assert::IsTrue(pt.getExpression(2).second.compare("abc*-d-") == 0);
            Assert::IsTrue(pt.getExpression(3).second.compare("abcd+*+e-") == 0);
            Assert::IsTrue(pt.getExpression(4).second.compare("a") == 0);
        }

        TEST_METHOD(TestMatchPatterns) {
            PatternTable pt;
            Assert::IsTrue(pt.addToPatternTable(1, "x", "a+b-c+d"));
            Assert::IsTrue(pt.addToPatternTable(2, "y", "a-b*c-d"));
            Assert::IsTrue(pt.addToPatternTable(3, "z", "a+b*(c+d)-e"));
            Assert::IsTrue(pt.addToPatternTable(4, "hello", "a"));

            // Test exact match
            Assert::IsTrue(pt.hasExactMatch(1, "a+b-c+d"));
            Assert::IsTrue(pt.hasExactMatch(2, "a-b*c-d"));
            Assert::IsTrue(pt.hasExactMatch(3, "a+b*(c+d)-e"));
            Assert::IsFalse(pt.hasExactMatch(1, "a+b"));

            // Test partial match
            Assert::IsTrue(pt.hasPartialMatch(1, "d"));
            Assert::IsTrue(pt.hasPartialMatch(1, "a+b"));
            Assert::IsTrue(pt.hasPartialMatch(2, "b*c"));
            Assert::IsTrue(pt.hasPartialMatch(1, "a+b-c+d"));
            Assert::IsTrue(pt.hasPartialMatch(3, "c+d"));
            Assert::IsTrue(pt.hasPartialMatch(4, "a"));

            Assert::IsFalse(pt.hasPartialMatch(2, "a-b"));
            Assert::IsFalse(pt.hasPartialMatch(3, "a+b"));
            Assert::IsFalse(pt.hasPartialMatch(3, "(c+d)-e"));
    
        }

        TEST_METHOD(TestGetMatchStmt)
        {
            PatternTable pt;
            Assert::IsTrue(pt.addToPatternTable(1, "a", "a+b"));
            Assert::IsTrue(pt.addToPatternTable(2, "b", "c-d"));
            Assert::IsTrue(pt.addToPatternTable(3, "a", "a+b+c"));
            Assert::IsTrue(pt.addToPatternTable(4, "c", "a-b-c"));
            Assert::IsTrue(pt.addToPatternTable(5, "d", "a+b+c"));
            Assert::IsTrue(pt.addToPatternTable(6, "e", "a+b+c"));

            // test for partial match
            list<int> expectedMatchStmt;
            expectedMatchStmt.push_back(3);
            expectedMatchStmt.push_back(5);
            expectedMatchStmt.push_back(6);

            list<int> testMatchStmt = pt.getExactMatchStmt("a+b+c");

            while (!testMatchStmt.empty() && !expectedMatchStmt.empty()) {
                Assert::AreEqual(testMatchStmt.front(), expectedMatchStmt.front());
                testMatchStmt.pop_front();
                expectedMatchStmt.pop_front();
            }

            list<int> expectedPartialMatchStmt;
            expectedPartialMatchStmt.push_back(1);
            expectedPartialMatchStmt.push_back(3);
            expectedPartialMatchStmt.push_back(5);
            expectedPartialMatchStmt.push_back(6);

            list<int> testPartialMatchStmt = pt.getPartialMatchStmt("a+b");

            while (!testPartialMatchStmt.empty() && !expectedPartialMatchStmt.empty()) {
                Assert::AreEqual(testPartialMatchStmt.front(), expectedPartialMatchStmt.front());
                testPartialMatchStmt.pop_front();
                expectedPartialMatchStmt.pop_front();
            }
        }
    };
}