#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SPA\PKB\UsesTableStmtToVar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting {
    TEST_CLASS(TestUsesTableStmtToVar)
    {
    public:
        TEST_METHOD(TestPopulate)
        {
            UsesTableStmtToVar usesTable;
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, "a"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, "b"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, "a"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, "b"));

            // check whether list is populated correctly
            list<string> templist;
            templist.push_back("a");
            templist.push_back("b");
            list<string> testlist = usesTable.getUsesVariablesFromStmt(1);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // check for zero duplicates
            templist.push_back("a");
            templist.push_back("b");
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, "b"));
            testlist = usesTable.getUsesVariablesFromStmt(2);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

        }

        TEST_METHOD(TestUses)
        {
            UsesTableStmtToVar usesTable;
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, "a"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, "b"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, "a"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(4, "c"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(7, "d"));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(888, "e"));


            Assert::IsTrue(usesTable.isUses(1, "a"));
            Assert::IsTrue(usesTable.isUses(1, "b"));
            Assert::IsTrue(usesTable.isUses(2, "a"));
            Assert::IsFalse(usesTable.isUses(2, "abc"));

            Assert::IsTrue(usesTable.isUsingAnything(1));
            Assert::IsFalse(usesTable.isUsingAnything(3));

            // test for stmt list
            list<int> expectedStmtList;
            expectedStmtList.push_back(1);
            expectedStmtList.push_back(2);
            expectedStmtList.push_back(4);
            expectedStmtList.push_back(7);
            expectedStmtList.push_back(888);

            list<int> testStmtList = usesTable.getStmtThatUses();
            testStmtList.sort();

            while (!expectedStmtList.empty() && !testStmtList.empty())
            {
                Assert::AreEqual(expectedStmtList.front(), testStmtList.front());
                expectedStmtList.pop_front();
                testStmtList.pop_front();
            }

            // test for pairs list
            list<pair<int, string>> expectedPairsList;
            expectedPairsList.push_back(make_pair(1, "a"));
            expectedPairsList.push_back(make_pair(1, "b"));
            expectedPairsList.push_back(make_pair(2, "a"));
            expectedPairsList.push_back(make_pair(4, "c"));
            expectedPairsList.push_back(make_pair(7, "d"));
            expectedPairsList.push_back(make_pair(888, "e"));

            list<pair<int, string>> testPairsList = usesTable.getUsesPairs();
            testPairsList.sort();

            while (!expectedPairsList.empty() && !testPairsList.empty())
            {
                Assert::AreEqual(expectedPairsList.front().first, testPairsList.front().first);
                Assert::AreEqual(expectedPairsList.front().second, testPairsList.front().second);
                expectedPairsList.pop_front();
                testPairsList.pop_front();
            }

        }
    };
}