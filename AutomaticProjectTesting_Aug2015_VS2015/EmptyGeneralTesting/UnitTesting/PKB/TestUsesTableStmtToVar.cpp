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
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, 1));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, 2));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, 1));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, 2));

            // check whether list is populated correctly
            list<int> templist;
            templist.push_back(1);
            templist.push_back(2);
            list<int> testlist = usesTable.getUsesVariablesFromStmt(1);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // check for zero duplicates
            templist.push_back(1);
            templist.push_back(2);
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, 2));
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
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, 1));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(1, 2));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(2, 1));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(4, 3));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(7, 4));
            Assert::IsTrue(usesTable.addUsesStmtToVarList(888, 5));


            Assert::IsTrue(usesTable.isUses(1, 1));
            Assert::IsTrue(usesTable.isUses(1, 2));
            Assert::IsTrue(usesTable.isUses(2, 1));
            Assert::IsFalse(usesTable.isUses(2, 142));

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
            // test for pairs list
            list<int> stmtList;
            stmtList.push_back(1);
            stmtList.push_back(1);
            stmtList.push_back(2);
            stmtList.push_back(4);
            stmtList.push_back(7);
            stmtList.push_back(888);

            list<int> usesList;
            usesList.push_back(1);
            usesList.push_back(2);
            usesList.push_back(1);
            usesList.push_back(3);
            usesList.push_back(4);
            usesList.push_back(5);

            pair<list<int>, list<int>> expectedPairList = make_pair(stmtList, usesList);
            pair<list<int>, list<int>> testPairList = usesTable.getUsesPair();

            while (!expectedPairList.first.empty() && !testPairList.first.empty()
                && !expectedPairList.second.empty() && !testPairList.second.empty())
            {
                Assert::IsTrue(usesTable.isUses(expectedPairList.first.front(), expectedPairList.second.front()));
                Assert::IsTrue(usesTable.isUses(testPairList.first.front(), testPairList.second.front()));
                expectedPairList.first.pop_front();
                expectedPairList.second.pop_front();
                testPairList.first.pop_front();
                testPairList.second.pop_front();
            }

        }
    };
}