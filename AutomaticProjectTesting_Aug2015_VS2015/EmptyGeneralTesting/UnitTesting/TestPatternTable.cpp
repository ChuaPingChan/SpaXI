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
            Assert::IsTrue(pt.addToPatternTable(1, "a+b-c+d"));
            Assert::IsTrue(pt.addToPatternTable(2, "a-b*c-d"));
            Assert::IsTrue(pt.addToPatternTable(3, "a+b*(c+d)-e"));
            Assert::IsTrue(pt.addToPatternTable(4, "a"));

            // check that the function rejects duplicated values
            Assert::IsFalse(pt.addToPatternTable(1, "a+b"));
            
            // postfix test
            Assert::IsTrue(pt.getExpression(1).compare("ab+c-d+") == 0);
            Assert::IsTrue(pt.getExpression(2).compare("abc*-d-") == 0);
            Assert::IsTrue(pt.getExpression(3).compare("abcd+*+e-") == 0);
            Assert::IsTrue(pt.getExpression(4).compare("a") == 0);
        }

        TEST_METHOD(TestMatchPatterns) {
            PatternTable pt;
            Assert::IsTrue(pt.addToPatternTable(1, "a+b-c+d"));
            Assert::IsTrue(pt.addToPatternTable(2, "a-b*c-d"));
            Assert::IsTrue(pt.addToPatternTable(3, "a+b*(c+d)-e"));
            Assert::IsTrue(pt.addToPatternTable(4, "a"));

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
    };
}