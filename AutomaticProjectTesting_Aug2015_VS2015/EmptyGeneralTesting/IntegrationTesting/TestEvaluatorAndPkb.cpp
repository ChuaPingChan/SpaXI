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
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "int", "2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 1 - Negative: Follows(int, int)
        TEST_METHOD(TestEvaluatorFollowsCase1Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "3", "int", "4" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 2 - Positive: Follows(int, _)
        TEST_METHOD(TestEvaluatorFollowsCase2Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 2 - Negative: Follows(int, _)
        TEST_METHOD(TestEvaluatorFollowsCase2Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "3", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 3 - Positive: Follows(int, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase3Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.setFollowsRel(2, 3);
            PKB.setFollowsRel(3, 4);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "2", "assign", "a" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_back("3");
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
            PKBMain PKB;
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
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
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "int", "2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 4 - Negative: Follows(_, int)
        TEST_METHOD(TestEvaluatorFollowsCase4Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "int", "4" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }

        //Case 5 - Positive: Follows(_, _)
        TEST_METHOD(TestEvaluatorFollowsCase5Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }
        
        //Case 5 - Negative: Follows(_, _)
        TEST_METHOD(TestEvaluatorFollowsCase5Negative)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "_", "", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
            Assert::IsFalse(qe.getHasResult());
        }
        
        //Case 6 - Positive: Follows(_, synonym)
        TEST_METHOD(TestEvaluatorFollowsCase6Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.setFollowsRel(2, 3);
            qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "_", "", "stmt", "s" };
            qe.evaluateFollowsTest(arrToEvaluate);
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
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            qe.setPkb(PKB);
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
            
        }

        //Case 7 - Negative: Follows(synonym, int)
        TEST_METHOD(TestEvaluatorFollowsCase7Negative)
        {

        }

        //Case 8 - Positive: Follows(synonym, _)
        TEST_METHOD(TestEvaluatorFollowsCase8Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.setFollowsRel(2, 3);
            qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s", "_", "" };
            qe.evaluateFollowsTest(arrToEvaluate);
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
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            qe.setPkb(PKB);
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
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.setFollowsRel(2, 3);
            qe.setPkb(PKB);
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            array<string, 4> arrToEvaluate = { "stmt", "s1", "stmt", "s2" };
            qe.evaluateFollowsTest(arrToEvaluate);
            expectedList1.push_back("1"); expectedList2.push_back("2");
            expectedList1.push_back("2"); expectedList2.push_back("3");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            assertPairContentIsTrue(expectedPair, actualPair);
        }

        void assertPairContentIsTrue(pair<list<string>, list<string>> expectedPair, pair<list<string>, list<string>> actualPair)
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

            //Case 9 - Negative: Follows(synonym, synonym)
            //TODO
        

        /*--------------- Evaluate FollowStar ---------------*/
        //Case 1 - Positive: FollowsStar(int, int)
        TEST_METHOD(TestEvaluateFollowsStarCase1Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.startProcessComplexRelations();
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "int", "2" };
            qe.evaluateFollowsTTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }
        
        //Case 2 - Positive: Follows(int, _)
        TEST_METHOD(TestEvaluateFollowStarCase2Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            qe.setPkb(PKB);
            PKB.startProcessComplexRelations();
            array<string, 4> arrToEvaluate = { "int", "1", "_", "" };
            qe.evaluateFollowsTTest(arrToEvaluate);
            Assert::IsTrue(qe.getHasResult());
        }

        //Case 3 - Positive: FollowsStar(int, synonym)
        TEST_METHOD(TestEvaluatorFollowStarCase3Positive)
        {
            qe = QueryEvaluator();
            qtInstance = qtInstance->clear();
            PKBMain PKB;
            list<string> expectedList1;
            list<string> expectedList2;
            pair<list<string>, list<string>> expectedPair;
            pair<list<string>, list<string>> actualPair;
            PKB.setFollowsRel(0, 1);
            PKB.setFollowsRel(1, 2);
            PKB.setFollowsRel(2, 3);
            PKB.setFollowsRel(3, 4);
            PKB.startProcessComplexRelations();
            qe.setPkb(PKB);
            array<string, 4> arrToEvaluate = { "int", "1", "assign", "a" };
            qe.evaluateFollowsTTest(arrToEvaluate);
            expectedList1.push_back("2");
            expectedList1.push_back("3");
            expectedList1.push_back("4");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe.getResultSuchThat();
            Assert::IsTrue(qe.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);
        }
       

    };
}