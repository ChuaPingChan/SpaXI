#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../SPA/PKB/PKBMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKBMain)
	{
	public:

		TEST_METHOD(TestPKBFollows)
		{
			PKBMain PKB;

			PKB.setFollowsRel(0, 1);
			PKB.setFollowsRel(1, 2);
			PKB.setFollowsRel(2, 3);
			PKB.setFollowsRel(0, 4);
			PKB.setFollowsRel(4, 5);
			PKB.setFollowsRel(5, 6);
			PKB.setFollowsRel(0, 7);
			PKB.setFollowsRel(6, 8);
			PKB.setFollowsRel(3, 9);
			PKB.setFollowsRel(9, 10);

			PKB.setParentChildRel(3, 4);
			PKB.setParentChildRel(3, 5);
			PKB.setParentChildRel(3, 6);
			PKB.setParentChildRel(6, 7);
			PKB.setParentChildRel(3, 8);

			Assert::AreEqual(PKB.getAfter(1), 2);
			Assert::AreEqual(PKB.getAfter(10), 0);
			list<int> allBefore = PKB.getAllBefore("STMT");
			allBefore.sort();

			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 1) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 2) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 3) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 4) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 5) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 6) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 7) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 8) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 9) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 10) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 0) != allBefore.end());

			list<int> allAfter = PKB.getAllAfter("STMT");
			allAfter.sort();
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 1) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 2) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 3) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 4) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 5) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 6) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 7) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 8) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 9) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 10) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 0) != allAfter.end());

			Assert::IsTrue(PKB.hasFollows());

			Assert::IsTrue(PKB.isFollows(1, 2));
			Assert::IsTrue(PKB.isFollows(2, 3));
			Assert::IsTrue(PKB.isFollows(4, 5));
			Assert::IsTrue(PKB.isFollows(5, 6));
			Assert::IsTrue(PKB.isFollows(6, 8));
			Assert::IsTrue(PKB.isFollows(3, 9));
			Assert::IsTrue(PKB.isFollows(9, 10));

			pair<list<int>, list<int>> allFollows = PKB.getAllFollows("WHILE", "WHILE");
			list<int> bef = allFollows.first;
			list<int> aft = allFollows.second;

			while (!bef.empty() && !aft.empty()) {
				Assert::IsTrue(PKB.isFollows(bef.front(), aft.front()));
				bef.pop_front();
				aft.pop_front();
			}

			PKB.startProcessComplexRelations();
			Assert::IsTrue(PKB.isFollowsStar(1, 10));

			list<int> allAfterStar = PKB.getAllAfterStar("STMT");
			allAfterStar.sort();
			list<int> expectedAfterStar;
			expectedAfterStar.push_back(2);
			expectedAfterStar.push_back(3);
			expectedAfterStar.push_back(5);
			expectedAfterStar.push_back(6);
			expectedAfterStar.push_back(8);
			expectedAfterStar.push_back(9);
			expectedAfterStar.push_back(10);

			Assert::IsTrue(allAfterStar == expectedAfterStar);

			list<int>allBeforeStar = PKB.getAllBeforeStar("STMT");
			allBeforeStar.sort();
			list<int> expectedBeforeStar;
			expectedBeforeStar = { 1, 2, 3, 4, 5, 6, 9 };

			Assert::IsTrue(expectedBeforeStar == allBeforeStar);

			pair<list<int>, list<int>> allFollowsStar = PKB.getAllFollowsStar("STMT", "STMT");
			Assert::IsTrue(allFollowsStar.first.size() == 16);

			// TESTPARENT

			/*Assert::IsTrue(PKB.isParent(3, 4));
			Assert::IsTrue(PKB.isParent(3, 5));
			Assert::IsTrue(PKB.isParent(3, 6));
			Assert::IsTrue(PKB.isParent(6, 7));
			Assert::IsTrue(PKB.isParent(3, 8));*/
			
		}

		TEST_METHOD(TestPKBFollows2) 
		{
			PKBMain PKB;
			PKB.setFollowsRel(0, 1);

			Assert::IsFalse(PKB.hasFollows());
		}
		
		TEST_METHOD(TestGeneralPurposeAPI)
        {
            PKBMain PKB;
            Assert::IsTrue(PKB.addAssignmentStmt(1));
            Assert::IsTrue(PKB.addAssignmentStmt(3));
            Assert::IsTrue(PKB.addAssignmentStmt(4));
            Assert::IsTrue(PKB.addAssignmentStmt(6));
            Assert::IsTrue(PKB.addAssignmentStmt(8));
            Assert::IsTrue(PKB.addWhileStmt(2));
            Assert::IsTrue(PKB.addWhileStmt(5));
            Assert::IsTrue(PKB.addWhileStmt(7));
            // test isAssignment
            Assert::IsTrue(PKB.isAssignment(6));
            Assert::IsFalse(PKB.isAssignment(7));
            // test isWhile
            Assert::IsTrue(PKB.isWhile(2));
            Assert::IsFalse(PKB.isWhile(3));
            // test isPresent
            Assert::IsTrue(PKB.addVariable("hello"));
            Assert::IsTrue(PKB.addVariable("kimochi"));
            Assert::IsTrue(PKB.isPresent(5));
            Assert::IsFalse(PKB.isPresent(9));
            Assert::IsTrue(PKB.isPresent("hello"));
            Assert::IsFalse(PKB.isPresent("world"));
            // test getWhiles
            Assert::IsFalse(PKB.addWhileStmt(5));
            list<int> expected;
            expected.push_back(2);
            expected.push_back(5);
            expected.push_back(7);
            list<int> test = PKB.getAllWhiles();
            while (!expected.empty() && !test.empty())
            {
                Assert::AreEqual(expected.front(), test.front());
                expected.pop_front();
                test.pop_front();
            }
        }

        TEST_METHOD(TestModifiesTable) {
            PKBMain PKB;
            Assert::IsTrue(PKB.setModTableStmtToVar(1, "a"));
            Assert::IsTrue(PKB.setModTableStmtToVar(1, "b"));
            Assert::IsTrue(PKB.setModTableStmtToVar(2, "a"));
            Assert::IsTrue(PKB.setModTableStmtToVar(4, "c"));
            Assert::IsTrue(PKB.setModTableStmtToVar(7, "d"));
            Assert::IsTrue(PKB.setModTableStmtToVar(888, "e"));

            // test getModifiesFromStmt
            list<string> templist;
            templist.push_back("a");
            templist.push_back("b");
            list<string> testlist = PKB.getModifiesFromStmt(1);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // check for zero duplicates
            templist.push_back("a");
            templist.push_back("b");
            Assert::IsTrue(PKB.setModTableStmtToVar(1, "a"));
            testlist = PKB.getModifiesFromStmt(2);
            while (!templist.empty() && !testlist.empty())
            {
                Assert::AreEqual(templist.front(), testlist.front());
                testlist.pop_front();
                templist.pop_front();
            }

            // test isMod
            Assert::IsTrue(PKB.isMod(1, "a"));
            Assert::IsTrue(PKB.isMod(1, "b"));
            Assert::IsTrue(PKB.isMod(2, "a"));
            Assert::IsFalse(PKB.isMod(2, "abc"));

            // test isModifyingAnything
            Assert::IsTrue(PKB.isModifyingAnything(1));
            Assert::IsFalse(PKB.isModifyingAnything(3));

            // test getStmtFromVar
            list<int> stmtList;
            stmtList.push_back(1);
            stmtList.push_back(2);
            list<int> testStmtList;
            testStmtList = PKB.getModifiesFromVar("a","stmt");
            while (!stmtList.empty() && !testStmtList.empty())
            {
                Assert::AreEqual(stmtList.front(), testStmtList.front());
                testStmtList.pop_front();
                stmtList.pop_front();
            }
            // test getStmtThatModifiesAnything
            
            // test getModPairs

            stmtList.push_back(1);
            stmtList.push_back(1);
            stmtList.push_back(2);
            stmtList.push_back(4);
            stmtList.push_back(7);
            stmtList.push_back(888);

            list<string> modList;
            modList.push_back("a");
            modList.push_back("b");
            modList.push_back("a");
            modList.push_back("c");
            modList.push_back("d");
            modList.push_back("e");


        }

        TEST_METHOD(TestUsesTable) {
            PKBMain PKB;
        }
	};
}