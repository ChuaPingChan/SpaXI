#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\PQL\QueryEvaluator.h"
#include "..\SPA\PKB\PKBMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestEvaluatorAndPkb)
    {
    public:
        QueryTree* qtInstance = QueryTree::getInstance();
		PKBMain* pkbInstance = PKBMain::getInstance();
        QueryEvaluator qe;

        // TEST_METHOD(TestEvaluatorSelect)
        // {
            
        // }

        /*--------------- Evaluate Follow ---------------*/
        //Case 1 - Positive: Follows(int, int)
        TEST_METHOD(TestEvaluatorFollowsCase1Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "int", "2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 1 - Negative: Follows(int, int)
        TEST_METHOD(TestEvaluatorFollowsCase1Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "3", "int", "4" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 2 - Positive: Follows(int, _)
        TEST_METHOD(TestEvaluatorFollowsCase2Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 2 - Negative: Follows(int, _)
        TEST_METHOD(TestEvaluatorFollowsCase2Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "3", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 3 - Positive: Follows(int, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase3Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            pkbInstance->setFollowsRel(3, 4);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "2", "stmt", "s" };
            qe.evaluateFollowsTest(arrToEvaluate);           
            expectedList1.push_back("3");
            expectedList1.push_front("s");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 3 - Negative: Follows(int, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase3Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "2", "assign", "a" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsFalse(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 4 - Positive: Follows(_, int)
        TEST_METHOD(TestEvaluatorFollowsCase4Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            pkbInstance->setFollowsRel(3, 8);
            pkbInstance->setFollowsRel(4, 5);
            pkbInstance->setFollowsRel(5, 6);
            pkbInstance->setFollowsRel(6, 7);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "int", "2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 4 - Negative: Follows(_, int)
        TEST_METHOD(TestEvaluatorFollowsCase4Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "int", "4" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 5 - Positive: Follows(_, _)
        TEST_METHOD(TestEvaluatorFollowsCase5Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }
        
        //Case 5 - Negative: Follows(_, _)
        TEST_METHOD(TestEvaluatorFollowsCase5Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }
        
        //Case 6 - Positive: Follows(_, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase6Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "_", "", "stmt", "s" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_front("s");
            expectedList1.push_back("2");
            expectedList1.push_back("3");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 6 - Negative: Follows(_, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase6Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "_", "", "stmt", "s" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsFalse(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 7 - Positive: Follows(synonym, int)
        TEST_METHOD(TestEvaluatorFollowsCase7Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s", "int", "2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_front(arrToEvaluate[1]);
            expectedList1.push_back("1");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 7 - Negative: Follows(synonym, int)
        TEST_METHOD(TestEvaluatorFollowsCase7Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s", "int", "1" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsFalse(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 8 - Positive: Follows(synonym, _)
        TEST_METHOD(TestEvaluatorFollowsCase8Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_front(arrToEvaluate[1]);
            expectedList1.push_back("1");
            expectedList1.push_back("2");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        //Case 8 - Negative: Follows(synonym, _)
        TEST_METHOD(TestEvaluatorFollowsCase8Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsFalse(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }
            
        //Case 9 - Positive: Follows(synonym, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase9Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            pkbInstance->setFollowsRel(1, 2);
            pkbInstance->setFollowsRel(2, 3);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s1", "stmt", "s2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_front(arrToEvaluate[1]); expectedList2.push_front(arrToEvaluate[3]);
            expectedList1.push_back("1"); expectedList2.push_back("2");
            expectedList1.push_back("2"); expectedList2.push_back("3");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            assertIsTruePairContent(expectedPair, actualPair);
        }

        //Case 9 - Negative: Follows(synonym, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase9Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance(); pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
            //qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s1", "stmt", "s2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsFalse(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }

        /*--------------- Evaluate FollowStar ---------------*/
        //Case 1 - Positive: FollowsStar(int, int)
        TEST_METHOD(TestEvaluateFollowsStarCase1Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
            pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
			pkbInstance->startProcessComplexRelations();
            array<string, 4> arrToEvaluate = { "int", "1", "int", "2" };
            qe.evaluateFollowsStarTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }
        
        //Case 2 - Positive: Follows(int, _)
        TEST_METHOD(TestEvaluateFollowStarCase2Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
			pkbInstance->startProcessComplexRelations();
            array<string, 4> arrToEvaluate = { "int", "1", "_", "" };
            qe.evaluateFollowsStarTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }
		
        //Case 3 - Positive: FollowsStar(int, synonym)
        TEST_METHOD(TestEvaluatorFollowStarCase3Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
            list<string> expectedList1;
            list<string> expectedList2;
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
			pkbInstance->setFollowsRel(2, 3);
			pkbInstance->setFollowsRel(3, 4);
			pkbInstance->startProcessComplexRelations();
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "stmt", "s" };
            qe.evaluateFollowsStarTest(arrToEvaluate);
            expectedList1.push_front("s");
            expectedList1.push_back("2");
            expectedList1.push_back("3");
            expectedList1.push_back("4");
			pair<list<string>, list<string>> expectedPair = make_pair(expectedList1, expectedList2);
			pair<list<string>, list<string>> actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }
       
        //Case 4 - Positive: FollowsStar(_, int)
        TEST_METHOD(TestEvaluatorFollowsStarCase4Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
			PKBMain::resetInstance();
			pkbInstance = PKBMain::getInstance();
			pkbInstance->setFollowsRel(0, 1);
			pkbInstance->setFollowsRel(1, 2);
			pkbInstance->setFollowsRel(4, 5);
			pkbInstance->setFollowsRel(9, 10);
			pkbInstance->setFollowsRel(10, 11);
			pkbInstance->startProcessComplexRelations();
            //qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "int", "10" };
            qe.evaluateFollowsStarTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        void assertIsTruePairContent(pair<list<string>, list<string>> expectedPair, pair<list<string>, list<string>> actualPair)
        {
            list<string> expected1stList = expectedPair.first;
            list<string> actual1stList = actualPair.first;
            Assert::AreEqual(expected1stList.size(), actual1stList.size());
            for (std::list<string>::iterator itExpected1 = expected1stList.begin(); itExpected1 != expected1stList.end(); ++itExpected1) {
                string itemFromExpected1stList = *itExpected1;

                std::list<string>::iterator itActual1 = find(actual1stList.begin(), actual1stList.end(), itemFromExpected1stList);
                Assert::IsTrue(itActual1 != actual1stList.end());
            }

            list<string> expected2ndList = expectedPair.second;
            list<string> actual2ndList = actualPair.second;
            Assert::AreEqual(expected2ndList.size(), actual2ndList.size());
            for (std::list<string>::iterator itExpected2 = expected2ndList.begin(); itExpected2 != expected2ndList.end(); ++itExpected2) {
                string itemFromExpected2ndList = *itExpected2;

                std::list<string>::iterator itActual2 = find(actual2ndList.begin(), actual2ndList.end(), itemFromExpected2ndList);
                Assert::IsTrue(itActual2 != actual2ndList.end());
            }
        }

        //Case 4 - Positive: Uses(synonym, ident)
        TEST_METHOD(TestEvaluatorUsesCase4Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain::resetInstance();
            pkbInstance = PKBMain::getInstance();
            pkbInstance->addVariable("j");
            pkbInstance->addVariable("a");
            pkbInstance->addVariable("c");
            pkbInstance->addVariable("d");
            pkbInstance->setUseTableStmtToVar(1,"j");
            pkbInstance->setUseTableStmtToVar(3, "a");
            pkbInstance->setUseTableStmtToVar(8, "c");
            pkbInstance->setUseTableStmtToVar(8, "d");
            pkbInstance->startProcessComplexRelations();
            //qe.setPkb(PKB);
            list<int> actualList = pkbInstance->getUsesFromVar("d", "stmt");
            list<int> expectedList;
            expectedList.push_back(8);
            Assert::IsTrue(expectedList == actualList);
        }

    };
}