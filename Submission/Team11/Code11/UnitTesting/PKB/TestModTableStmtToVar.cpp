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
            Assert::IsTrue(modTable.addModStmtToVarList(1, 1));
            Assert::IsTrue(modTable.addModStmtToVarList(1, 2));
            Assert::IsTrue(modTable.addModStmtToVarList(2, 1));
            Assert::IsTrue(modTable.addModStmtToVarList(2, 2));
            
            // check whether list is populated correctly
            list<int> templist;
            templist.push_back(1);
            templist.push_back(2);
            list<int> testlist = modTable.getModVariablesFromStmt(1);
            while (!templist.empty() && !testlist.empty()) 
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // check for zero duplicates
            templist.push_back(1);
            templist.push_back(2);
            Assert::IsTrue(modTable.addModStmtToVarList(2, 2));
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
            Assert::IsTrue(modTable.addModStmtToVarList(1, 1));
            Assert::IsTrue(modTable.addModStmtToVarList(1, 2));
            Assert::IsTrue(modTable.addModStmtToVarList(2, 1));
            Assert::IsTrue(modTable.addModStmtToVarList(4, 3));
            Assert::IsTrue(modTable.addModStmtToVarList(7, 4));
            Assert::IsTrue(modTable.addModStmtToVarList(888, 5));
            

            Assert::IsTrue(modTable.isMod(1, 1));
            Assert::IsTrue(modTable.isMod(1, 2));
            Assert::IsTrue(modTable.isMod(2, 1));
            Assert::IsFalse(modTable.isMod(2, 123));

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
            list<int> stmtList;
            stmtList.push_back(1);
            stmtList.push_back(1);
            stmtList.push_back(2);
            stmtList.push_back(4);
            stmtList.push_back(7);
            stmtList.push_back(888);

            list<int> modList;
            modList.push_back(1);
            modList.push_back(2);
            modList.push_back(1);
            modList.push_back(3);
            modList.push_back(4);
            modList.push_back(5);

            pair<list<int>, list<int>> expectedPairList = make_pair(stmtList, modList);
            pair<list<int>,list<int>> testPairList = modTable.getModPair();
            
            while (!expectedPairList.first.empty() && !testPairList.first.empty()
                && !expectedPairList.second.empty() && !testPairList.second.empty())
            {
                Assert::IsTrue(modTable.isMod(expectedPairList.first.front(), expectedPairList.second.front()));
                Assert::IsTrue(modTable.isMod(testPairList.first.front(), testPairList.second.front()));
                expectedPairList.first.pop_front();
                expectedPairList.second.pop_front();
                testPairList.first.pop_front();
                testPairList.second.pop_front();
            }
            
        }
    };
}