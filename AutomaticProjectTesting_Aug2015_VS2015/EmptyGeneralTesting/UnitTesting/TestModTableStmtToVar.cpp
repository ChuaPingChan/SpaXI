#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SPA\PKB\ModTableStmtToVar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting {
    TEST_CLASS(TestModTableStmtToVar) 
    {
    public:
        TEST_METHOD(TestPopulate) 
        {
            ModTableStmtToVar modTable;
            Assert::IsTrue(modTable.addModStmtToVarList(1, "a"));
            Assert::IsTrue(modTable.addModStmtToVarList(1, "b"));
            Assert::IsTrue(modTable.addModStmtToVarList(2, "a"));
            Assert::IsTrue(modTable.addModStmtToVarList(2, "b"));
            
            // check whether list is populated correctly
            list<string> templist;
            templist.push_back("a");
            templist.push_back("b");
            list<string> testlist = modTable.getModVariablesFromStmt(1);
            while (!templist.empty() && !testlist.empty()) 
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // check for zero duplicates
            templist.push_back("a");
            templist.push_back("b");
            Assert::IsTrue(modTable.addModStmtToVarList(2, "b"));
            testlist = modTable.getModVariablesFromStmt(2);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

        }

        TEST_METHOD(TestMod)
        {
            ModTableStmtToVar modTable;
            Assert::IsTrue(modTable.addModStmtToVarList(1, "a"));
            Assert::IsTrue(modTable.addModStmtToVarList(1, "b"));
            Assert::IsTrue(modTable.addModStmtToVarList(2, "a"));
            Assert::IsTrue(modTable.addModStmtToVarList(4, "c"));
            Assert::IsTrue(modTable.addModStmtToVarList(7, "d"));
            Assert::IsTrue(modTable.addModStmtToVarList(888, "e"));
            

            Assert::IsTrue(modTable.isMod(1, "a"));
            Assert::IsTrue(modTable.isMod(1, "b"));
            Assert::IsTrue(modTable.isMod(2, "a"));
            Assert::IsFalse(modTable.isMod(2, "abc"));

            Assert::IsTrue(modTable.isModifyingAnything(1));
            Assert::IsFalse(modTable.isModifyingAnything(3));
            
            // test for stmt list
            list<int> expectedStmtList;
            expectedStmtList.push_back(1);
            expectedStmtList.push_back(2);
            expectedStmtList.push_back(4);
            expectedStmtList.push_back(7);
            expectedStmtList.push_back(888);

            list<int> testStmtList = modTable.getStmtThatModifies();
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

            list<pair<int, string>> testPairsList = modTable.getModPairs();
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