#include "CppUnitTest.h"
#include <string>
#include "../SPA/PKB/PKBMain.h"
#include "../SPA/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKBMain)
	{
	public:

		TEST_METHOD(TestPKBFollowsAndParents)
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
			list<int> allBefore = PKB.getAllBefore(STMT);
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

			list<int> allAfter = PKB.getAllAfter(STMT);
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

			pair<list<int>, list<int>> allFollows = PKB.getAllFollows(WHILE, WHILE);
			list<int> bef = allFollows.first;
			list<int> aft = allFollows.second;

			while (!bef.empty() && !aft.empty()) {
				Assert::IsTrue(PKB.isFollows(bef.front(), aft.front()));
				bef.pop_front();
				aft.pop_front();
			}

			PKB.startProcessComplexRelations();
			Assert::IsTrue(PKB.isFollowsStar(1, 10));

			list<int> allAfterStar = PKB.getAllAfterStar(STMT);
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

			list<int>allBeforeStar = PKB.getAllBeforeStar(STMT);
			allBeforeStar.sort();
			list<int> expectedBeforeStar;
			expectedBeforeStar = { 1, 2, 3, 4, 5, 6, 9 };

			Assert::IsTrue(expectedBeforeStar == allBeforeStar);

			pair<list<int>, list<int>> allFollowsStar = PKB.getAllFollowsStar(STMT, STMT);
			Assert::IsTrue(allFollowsStar.first.size() == 16);

			// TESTPARENT

			Assert::IsTrue(PKB.isParentChild(3, 4));
			Assert::IsTrue(PKB.isParentChild(3, 5));
			Assert::IsTrue(PKB.isParentChild(3, 6));
			Assert::IsTrue(PKB.isParentChild(6, 7));
			Assert::IsTrue(PKB.isParentChild(3, 8));

			Assert::IsTrue(PKB.isParent(3));
			Assert::IsTrue(PKB.isParent(6));

			list<int> children;
			children = PKB.getChildren(3, STMT);
			children.sort();
			list<int> expectedChildren = { 4, 5, 6, 8 };

			list<int> allChildren;
			allChildren = PKB.getAllChildren(STMT);
			allChildren.sort();
			list<int> expectedAllChildren = { 4, 5, 6, 7, 8 };

			Assert::IsTrue(allChildren == expectedAllChildren);
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
            string dummyVarName = "dummyVar";

            Assert::IsTrue(PKB.addAssignmentStmt(1));
            Assert::IsTrue(PKB.addAssignmentStmt(3));
            Assert::IsTrue(PKB.addAssignmentStmt(4));
            Assert::IsTrue(PKB.addAssignmentStmt(6));
            Assert::IsTrue(PKB.addAssignmentStmt(8));
            Assert::IsTrue(PKB.addWhileStmt(2, dummyVarName));
            Assert::IsTrue(PKB.addWhileStmt(5, dummyVarName));
            Assert::IsTrue(PKB.addWhileStmt(7, dummyVarName));
            Assert::IsTrue(PKB.addIfStmt(9, dummyVarName));
            Assert::IsTrue(PKB.addIfStmt(10, dummyVarName));
            Assert::IsTrue(PKB.addAssignmentStmt(11));
            // test isAssignment
            Assert::IsTrue(PKB.isAssignment(6));
            Assert::IsFalse(PKB.isAssignment(7));
            // test isWhile
            Assert::IsTrue(PKB.isWhile(2));
            Assert::IsFalse(PKB.isWhile(3));
            // test isIf
            Assert::IsTrue(PKB.isIf(10));
            Assert::IsFalse(PKB.isIf(8));
            // test isPresent
            Assert::IsTrue(PKB.addVariable("hello"));
            Assert::IsTrue(PKB.addVariable("kimochi"));
            Assert::IsTrue(PKB.isPresent(5));
            Assert::IsFalse(PKB.isPresent(12));
            Assert::IsTrue(PKB.isPresent("hello"));
            Assert::IsFalse(PKB.isPresent("world"));
            // test getWhiles
            Assert::IsTrue(PKB.addWhileStmt(5, dummyVarName));  // Don't mind duplicates
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
            // test getAssigns
            expected.push_back(1);
            expected.push_back(3);
            expected.push_back(4);
            expected.push_back(6);
            expected.push_back(8);
            expected.push_back(11);
            list<int> testAssign = PKB.getAllAssignments();
            while (!expected.empty() && !testAssign.empty())
            {
                Assert::AreEqual(expected.front(), testAssign.front());
                expected.pop_front();
                testAssign.pop_front();
            }
            // test getIfs
            expected.push_back(9);
            expected.push_back(10);
            list<int> testIf = PKB.getAllIfs();
            Assert::IsTrue(expected == testIf);
        }

        TEST_METHOD(TestModifiesTable) {
            PKBMain PKB;
			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.addVariable("c");
			PKB.addVariable("d");
			PKB.addVariable("e");
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
            list<int> testIntlist = PKB.getModifiesFromStmt(1);
			list<string> testlist = PKB.convertIdxToString(testIntlist, STMT);
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
            testlist = PKB.convertIdxToString(PKB.getModifiesFromStmt(2), STMT);
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
            testStmtList = PKB.getModifiesFromVar("a", STMT);
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

		TEST_METHOD(TestCallsTable) {
			PKBMain PKB;
			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.addVariable("c");
			PKB.addVariable("d");
			PKB.addVariable("e");
			PKB.addVariable("f");
			PKB.addVariable("g");
			PKB.addVariable("h");
			PKB.addVariable("i");
			PKB.addProcedure("One");
			PKB.setCallsRel(2, "One", "Two");
			PKB.setCallsRel(3, "One", "Three");
			PKB.setUseTableProcToVar("One", "a");
			PKB.addProcedure("Three");
			PKB.setCallsRel(6, "Three", "Four");
			PKB.setCallsRel(7, "Three", "Five");
			PKB.setCallsRel(8, "Three", "Six");
			PKB.addProcedure("Four");
			PKB.addProcedure("Five");
			PKB.setCallsRel(14, "Five", "Six");
			PKB.setCallsRel(15, "Five", "Seven");
			PKB.setUseTableProcToVar("Five", "b");
			PKB.addProcedure("Six");
			PKB.setCallsRel(19, "Six", "Seven");
			PKB.addProcedure("Two");
			PKB.setCallsRel(24, "Two", "Eight");
			PKB.addProcedure("Seven");
			PKB.setCallsRel(28, "Seven", "Nine");
			PKB.addProcedure("Eight");
			PKB.setCallsRel(33, "Eight", "Nine");
			PKB.addProcedure("Nine");
			PKB.setUseTableProcToVar("Nine", "c");
			PKB.setModTableProcToVar("One", "a");
			PKB.setModTableProcToVar("Two", "b");
			PKB.setModTableProcToVar("Three", "c");
			PKB.setModTableProcToVar("Four", "d");
			PKB.setModTableProcToVar("Five", "e");
			PKB.setModTableProcToVar("Six", "f");
			PKB.setModTableProcToVar("Seven", "g");
			PKB.setModTableProcToVar("Eight", "h");
			PKB.setModTableProcToVar("Nine", "i");

			PKB.startProcessComplexRelations();

			Assert::IsTrue(PKB.isCallsStar("One", "Nine"));
			Assert::IsTrue(PKB.isUsesProc("One", "a"));
			Assert::IsTrue(PKB.isUsesProc("One", "b"));
			Assert::IsTrue(PKB.isUsesProc("One", "c"));
			Assert::IsTrue(PKB.isModProc("Three", "d"));
			Assert::IsTrue(PKB.isModProc("One", "d"));
			Assert::IsTrue(PKB.isUsesProc("Two", "c"));
			Assert::IsTrue(PKB.isUsesProc("Five", "c"));
			Assert::IsTrue(PKB.isUsesProc("Nine", "c"));
			Assert::IsTrue(PKB.isModProc("One", "a"));
			Assert::IsTrue(PKB.isModProc("One", "b"));
			Assert::IsTrue(PKB.isModProc("One", "c"));
			Assert::IsTrue(PKB.isModProc("Two", "h"));
			Assert::IsFalse(PKB.isModProc("Four", "h"));

			/*
			Index of proc are as follows
			"One" 0
			"Two" 1
			"Three" 2
			"Four" 3
			"Five" 4
			"Six" 5
			"Seven" 6
			"Eight" 7
			"Nine" 8
			*/

			list<int> expectedList = { 5, 4, 2, 0 };
			expectedList.sort();
			list<int> resultList = PKB.getCallerStar("Seven");
			resultList.sort();
			Assert::IsTrue(resultList == expectedList);
			expectedList = { 3, 4, 5, 6, 8 };
			expectedList.sort();
			resultList = PKB.getCalleeStar("Three");
			resultList.sort();
			Assert::IsTrue(resultList == expectedList);
			pair<list<int>, list<int>> allCallsStar = PKB.getAllCallsStar();
			Assert::IsTrue(PKB.isCallsStar(0, 2));
			Assert::IsTrue(PKB.isCallsStar(0, 3));
			Assert::IsTrue(PKB.isCallsStar(0, 4));
			Assert::IsTrue(PKB.isCallsStar(0, 5));
			Assert::IsTrue(PKB.isCallsStar(0, 6));
			Assert::IsTrue(PKB.isCallsStar(0, 7));
			Assert::IsTrue(PKB.isCallsStar(0, 8));
			Assert::IsTrue(PKB.isCallsStar(1, 7));
			Assert::IsFalse(PKB.isCallsStar(1, 6));
			Assert::IsFalse(PKB.isCallsStar(1, 4));
			Assert::IsTrue(PKB.isCallsStar(1, 8));



		}

		TEST_METHOD(TestInterproc) {
			PKBMain PKB;
			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.addVariable("c");
			PKB.addVariable("d");
			PKB.addVariable("e");
			PKB.addVariable("f");
			PKB.addVariable("g");
			PKB.addVariable("h");
			PKB.addVariable("i");
			PKB.addVariable("j");
			PKB.addVariable("k");
			PKB.addVariable("l");
			PKB.addVariable("m");
			PKB.addVariable("n");
			PKB.addVariable("o");
			PKB.addVariable("p");
			PKB.addVariable("q");
			PKB.addVariable("r");
			PKB.addVariable("s");
			PKB.addVariable("t");
			PKB.addVariable("u");
			PKB.addVariable("v");
			PKB.addVariable("w");
			PKB.addVariable("x");
			PKB.addVariable("y");
			PKB.addVariable("z");
			PKB.addProcedure("One");
			PKB.addProcedure("Two");
			PKB.addProcedure("Three");
			PKB.addProcedure("Four");
			PKB.addProcedure("Five");
			PKB.addProcedure("Six");
			PKB.addProcedure("Seven");
			PKB.addProcedure("Eight");
			PKB.addProcedure("Nine");
			PKB.addWhileStmt(1, "a");
			PKB.setUseTableStmtToVar(1, "a");
			PKB.setUseTableProcToVar("One", "a");
			PKB.setCallsRel(2, "One", "Two");
			PKB.setCallsRel(3, "One", "Three");
			PKB.setUseTableProcToVar("Three", "c");
			PKB.setUseTableProcToVar("Three", "d");
			PKB.setModTableProcToVar("Three", "b");
			PKB.setUseTableStmtToVar(4, "c");
			PKB.setUseTableStmtToVar(4, "d");
			PKB.setModTableStmtToVar(4, "b");
			PKB.addIfStmt(5, "e");
			PKB.setCallsRel(6, "Three", "Four");
			PKB.setCallsRel(7, "Three", "Five");
			PKB.setCallsRel(8, "Three", "Six");
			PKB.addWhileStmt(9, "f");
			PKB.setUseTableProcToVar("Four", "f");
			PKB.setUseTableStmtToVar(9, "f");
			PKB.setUseTableProcToVar("Four", "h");
			PKB.setUseTableProcToVar("Four", "a");
			PKB.setUseTableStmtToVar(10, "h");
			PKB.setUseTableStmtToVar(10, "a");
			PKB.setModTableProcToVar("Four", "g");
			PKB.setModTableStmtToVar(10, "g");
			PKB.setUseTableProcToVar("Five", "i");
			PKB.setUseTableStmtToVar(11, "i");
			PKB.addWhileStmt(11, "i");
			PKB.setUseTableProcToVar("Five", "a");
			PKB.setUseTableProcToVar("Five", "h");
			PKB.setUseTableStmtToVar(12, "a");
			PKB.setUseTableStmtToVar(12, "h");
			PKB.setModTableProcToVar("Five", "j");
			PKB.setModTableStmtToVar(12, "j");
			PKB.setUseTableProcToVar("Five", "j");
			PKB.addIfStmt(13, "j");
			PKB.setCallsRel(14, "Five", "Six");
			PKB.setCallsRel(15, "Five", "Seven");
			PKB.setUseTableProcToVar("Five", "j");
			PKB.setUseTableProcToVar("Five", "g");
			PKB.setUseTableProcToVar("Five", "a");
			PKB.setUseTableStmtToVar(16, "j");
			PKB.setUseTableStmtToVar(16, "g");
			PKB.setUseTableStmtToVar(16, "a");
			PKB.setModTableProcToVar("Five", "k");
			PKB.setModTableStmtToVar(16, "k");
			PKB.setUseTableProcToVar("Six", "m");
			PKB.setUseTableProcToVar("Six", "a");
			PKB.setUseTableStmtToVar(17, "m");
			PKB.setUseTableStmtToVar(17, "a");
			PKB.setModTableProcToVar("Six", "l");
			PKB.setModTableStmtToVar(17, "l");
			PKB.setUseTableProcToVar("Six", "m");
			PKB.setUseTableStmtToVar(18, "m");
			PKB.addIfStmt(18, "m");


		}

		TEST_METHOD(TestNextStar) {
			PKBMain PKB;
			PKB.setNext(49, 50);
			PKB.setNext(50, 51);
			PKB.setNext(50, 54);
			PKB.setNext(51, 52);
			PKB.setNext(51, 54);
			PKB.setNext(51, 50);
			PKB.setNext(52, 53);
			PKB.setNext(53, 51);
			PKB.setNext(53, 50);
			PKB.setNext(53, 54);

			Assert::IsTrue(PKB.isNextStar(53, 50));
			Assert::IsFalse(PKB.isNextStar(54, 49));
		}

		TEST_METHOD(TestAffects) {
			PKBMain PKB;
			PKB.setNext(1, 2);
			PKB.setNext(2, 3);
			PKB.setNext(3, 4);
			PKB.setNext(3, 5);
			PKB.setNext(4, 1);
			PKB.setNext(5, 1);
			PKB.setNext(1, 6);

			PKB.addStmtToProc(1, "Test");
			PKB.addStmtToProc(2, "Test");
			PKB.addStmtToProc(3, "Test");
			PKB.addStmtToProc(4, "Test");
			PKB.addStmtToProc(5, "Test");
			PKB.addStmtToProc(6, "Test");

			PKB.addVariable("d");
			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.addVariable("c");
			
			PKB.addWhileStmt(1, "d");
			PKB.addAssignmentStmt(2);
			PKB.setUseTableStmtToVar(2, "b");
			PKB.setModTableStmtToVar(2, "a");
			PKB.addIfStmt(3, "a");
			PKB.addAssignmentStmt(4);
			PKB.setModTableStmtToVar(4, "b");
			PKB.setUseTableStmtToVar(4, "c");
			PKB.addAssignmentStmt(5);
			PKB.setModTableStmtToVar(5, "c");
			PKB.setUseTableStmtToVar(5, "a");
			PKB.addAssignmentStmt(6);
			PKB.setModTableStmtToVar(6, "d");
			PKB.setUseTableStmtToVar(6, "a");
			PKB.setParentChildRel(1, 2);
			PKB.setParentChildRel(1, 3);
			PKB.setParentChildRel(3, 4);
			PKB.setParentChildRel(3, 5);
			PKB.startProcessComplexRelations();
			Assert::IsTrue(PKB.isAffects(2, 5));
			Assert::IsTrue(PKB.isAffects(5, 4));
			Assert::IsFalse(PKB.isAffects(4, 6));
			list<int> expectedList = { 2, 4, 5, 6 };
			list<int> resultList = PKB.getAllAffected();
			resultList.sort();
			Assert::IsTrue(expectedList == resultList);

			expectedList = { 2, 4, 5 };
			resultList = PKB.getAllAffector();
			resultList.sort();
			Assert::IsTrue(expectedList == resultList);
		}

		TEST_METHOD(TestAffectsPair) {
			PKBMain PKB;
			/*
			procedure Test {
			1.	a = 1;
			2.	b = a;
			3.	a = b;
			4.	b = a;
			}
			*/
			PKB.addProcedure("Test");
			PKB.setNext(1, 2);
			PKB.setNext(2, 3);
			PKB.setNext(3, 4);
			PKB.addStmtToProc(1, "Test");
			PKB.addStmtToProc(2, "Test");
			PKB.addStmtToProc(3, "Test");
			PKB.addStmtToProc(4, "Test");
			PKB.addAssignmentStmt(1);
			PKB.addAssignmentStmt(2);
			PKB.addAssignmentStmt(3);
			PKB.addAssignmentStmt(4);
			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.setModTableStmtToVar(1, "a");
			PKB.setModTableStmtToVar(2, "b");
			PKB.setUseTableStmtToVar(2, "a");
			PKB.setModTableStmtToVar(3, "a");
			PKB.setUseTableStmtToVar(3, "b");
			PKB.setUseTableStmtToVar(4, "a");
			PKB.setModTableStmtToVar(4, "b");

			pair<list<int>, list<int>> resultPair = PKB.getAllAffects();
			Assert::IsTrue(resultPair.first.size() == 3);
			Assert::IsTrue(resultPair.second.size() == 3);
		}

		TEST_METHOD(TestAffectsPairACW) { //affects, calls, while
			PKBMain PKB;

			/*
			procedure Test {
			1.	a = 3;
			2.	while b {
			3.		a = b + c;
			4.		b = 7;
			5.		call Test2; // modifies b, c
			6.		c = 3 + a;
			7.		b = a;
				}
			8.	c = a + b;
			}

			procedure Test2 { // modifies b, c
			9.	c = 2;
			10.	b = c;
			}
			*/

			PKB.addVariable("a");
			PKB.addVariable("b");
			PKB.addVariable("c");

			PKB.addProcedure("Test");
			PKB.addProcedure("Test2");

			PKB.addStmtToProc(1, "Test");
			PKB.addStmtToProc(2, "Test");
			PKB.addStmtToProc(3, "Test");
			PKB.addStmtToProc(4, "Test");
			PKB.addStmtToProc(5, "Test");
			PKB.addStmtToProc(6, "Test");
			PKB.addStmtToProc(7, "Test");
			PKB.addStmtToProc(8, "Test");
			PKB.addStmtToProc(9, "Test2");
			PKB.addStmtToProc(10, "Test2");

			PKB.setNext(1, 2);
			PKB.setNext(2, 3);
			PKB.setNext(3, 4);
			PKB.setNext(4, 5);
			PKB.setNext(5, 6);
			PKB.setNext(6, 7);
			PKB.setNext(7, 2);
			PKB.setNext(2, 8);
			PKB.setNext(9, 10);

			PKB.addAssignmentStmt(1);
			PKB.setModTableStmtToVar(1, "a");

			PKB.addWhileStmt(2, "b");

			PKB.setParentChildRel(2, 3);
			PKB.addAssignmentStmt(3);
			PKB.setModTableStmtToVar(3, "a");
			PKB.setUseTableStmtToVar(3, "b");
			PKB.setUseTableStmtToVar(3, "c");

			PKB.setParentChildRel(2, 4);
			PKB.addAssignmentStmt(4);
			PKB.setModTableStmtToVar(4, "b");

			PKB.setParentChildRel(2, 5);
			PKB.setCallsRel(5, "Test", "Test2");

			PKB.setParentChildRel(2, 6);
			PKB.addAssignmentStmt(6);
			PKB.setModTableStmtToVar(6, "c");
			PKB.setUseTableStmtToVar(6, "a");

			PKB.setParentChildRel(2, 7);
			PKB.addAssignmentStmt(7);
			PKB.setModTableStmtToVar(7, "b");
			PKB.setUseTableStmtToVar(7, "a");

			PKB.addAssignmentStmt(8);
			PKB.setModTableStmtToVar(8, "c");
			PKB.setUseTableStmtToVar(8, "a");
			PKB.setUseTableStmtToVar(8, "b");

			PKB.addAssignmentStmt(9);
			PKB.setModTableStmtToVar(9, "c");
			
			PKB.addAssignmentStmt(10);
			PKB.setModTableStmtToVar(10, "b");
			PKB.setUseTableStmtToVar(10, "c");

			PKB.setModTableProcToVar("Test", "a");
			PKB.setModTableProcToVar("Test", "b");
			PKB.setModTableProcToVar("Test", "c");
			PKB.setUseTableProcToVar("Test", "b");
			PKB.setUseTableProcToVar("Test", "c");
			PKB.setUseTableProcToVar("Test", "a");

			PKB.setModTableProcToVar("Test2", "c");
			PKB.setModTableProcToVar("Test2", "b");
			PKB.setUseTableProcToVar("Test2", "c");

			PKB.startProcessComplexRelations();

			Assert::IsTrue(PKB.isModProc(1, 2));
			Assert::IsTrue(PKB.isModProc("Test2", "c"));
			Assert::IsTrue(PKB.isModProc("Test2", "b"));
			Assert::IsFalse(PKB.isModProc("Test2", "a"));

			Assert::IsTrue(PKB.isAffects(1, 8));
			Assert::IsTrue(PKB.isAffects(3, 6));
			Assert::IsTrue(PKB.isAffects(3, 7));
			Assert::IsTrue(PKB.isAffects(6, 3));
			Assert::IsTrue(PKB.isAffects(7, 3));
			Assert::IsTrue(PKB.isAffects(7, 8));
			Assert::IsTrue(PKB.isAffects(9, 10));
			Assert::IsFalse(PKB.isAffects(1, 6));
			Assert::IsFalse(PKB.isAffects(1, 7));
			Assert::IsFalse(PKB.isAffects(6, 8));

			pair<list<int>, list<int>> resultPair = PKB.getAllAffects();
			int size = resultPair.first.size();
			Assert::IsTrue(resultPair.first.size() == 8);
		}
	};
}