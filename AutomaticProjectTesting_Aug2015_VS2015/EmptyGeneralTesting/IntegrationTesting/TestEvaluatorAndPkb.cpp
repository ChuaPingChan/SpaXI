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
        TEST_METHOD(TestEvaluatorFollowCase1Positive)
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
        TEST_METHOD(TestEvaluatorFollowCase1Negative)
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
        TEST_METHOD(TestEvaluatorFollowCase2Positive)
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
        TEST_METHOD(TestEvaluatorFollowCase2Negative)
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
        TEST_METHOD(TestEvaluatorFollowCase3Positive)
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
        TEST_METHOD(TestEvaluatorFollowCase3Negative)
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
        TEST_METHOD(TestEvaluatorFollowCase4Positive)
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
        TEST_METHOD(TestEvaluatorFollowCase4Negative)
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
        TEST_METHOD(TestEvaluatorFollowCase5Positive)
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
        TEST_METHOD(TestEvaluatorFollowCase5Negative)
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
        TEST_METHOD(TestEvaluatorFollowCase6Positive)
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
            //TODO

            //Case 7 - Positive: Follows(synonym, int)
            //TODO

            //Case 7 - Negative: Follows(synonym, int)
            //TODO

            //Case 8 - Positive: Follows(synonym, _)
            //TODO

            //Case 8 - Negative: Follows(synonym, _)
            //TODO

            //Case 9 - Positive: Follows(synonym, synonym)
            //TODO

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