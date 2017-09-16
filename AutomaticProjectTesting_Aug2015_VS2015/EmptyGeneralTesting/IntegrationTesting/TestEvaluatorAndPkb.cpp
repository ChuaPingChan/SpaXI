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
        list<string> expectedList1;
        list<string> expectedList2;
        pair<list<string>, list<string>> expectedPair;
        pair<list<string>, list<string>> actualPair;

       // TEST_METHOD(TestEvaluatorSelect)
       // {
            
       // }

        TEST_METHOD(TestEvaluatorFollows)
        {
            //Case 1 - Positive: Follows(int, int)
            QueryEvaluator qe1Positive = QueryEvaluator();
            PKBMain PKB1Positive;
            PKB1Positive.setFollowsRel(0, 1);
            PKB1Positive.setFollowsRel(1, 2);
            qe1Positive.setPkb(PKB1Positive);
            array<string, 4> arrToEvaluate1Positive = { "int", "1", "int", "2" };
            qe1Positive.evaluateFollowsTest(arrToEvaluate1Positive);
            Assert::IsTrue(qe1Positive.getHasResult());

            //Case 1 - Negative: Follows(int, int)
            QueryEvaluator qe1Negative = QueryEvaluator();
            PKBMain PKB1Negative;
            PKB1Negative.setFollowsRel(0, 1);
            PKB1Negative.setFollowsRel(1, 2);
            qe1Negative.setPkb(PKB1Negative);
            array<string, 4> arrToEvaluate1Negative = { "int", "3", "int", "4" };
            qe1Negative.evaluateFollowsTest(arrToEvaluate1Negative);
            Assert::IsFalse(qe1Negative.getHasResult());

            //Case 2 - Positive: Follows(int, _)
            QueryEvaluator qe2Positive = QueryEvaluator();
            PKBMain PKB2Positive;
            PKB2Positive.setFollowsRel(0, 1);
            PKB2Positive.setFollowsRel(1, 2);
            qe2Positive.setPkb(PKB2Positive);
            array<string, 4> arrToEvaluate2Positive = { "int", "1", "_", "" };
            qe2Positive.evaluateFollowsTest(arrToEvaluate2Positive);
            Assert::IsTrue(qe2Positive.getHasResult());

            //Case 2 - Negative: Follows(int, _)
            QueryEvaluator qe2Negative = QueryEvaluator();
            PKBMain PKB2Negative;
            PKB2Negative.setFollowsRel(0, 1);
            PKB2Negative.setFollowsRel(1, 2);
            qe2Negative.setPkb(PKB2Negative);
            array<string, 4> arrToEvaluate2Negative = { "int", "3", "_", "" };
            qe2Negative.evaluateFollowsTest(arrToEvaluate2Negative);
            Assert::IsFalse(qe2Negative.getHasResult());

            //Case 3 - Positive: Follows(int, synonym)
            QueryEvaluator qe3Positive = QueryEvaluator();
            PKBMain PKB3Positive;
            expectedList1.clear();
            expectedList2.clear();
            expectedPair = getEmptyPairOfListOfString();
            actualPair = getEmptyPairOfListOfString();
            PKB3Positive.setFollowsRel(0, 1);
            PKB3Positive.setFollowsRel(1, 2);
            PKB3Positive.setFollowsRel(2, 3);
            PKB3Positive.setFollowsRel(3, 4);
            qe3Positive.setPkb(PKB3Positive);
            array<string, 4> arrToEvaluate3Positive = { "int", "2", "assign", "a" };
            qe3Positive.evaluateFollowsTest(arrToEvaluate3Positive);
            expectedList1.push_back("3");
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe3Positive.getResultSuchThat();
            Assert::IsTrue(qe3Positive.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);

            //Case 3 - Negative: Follows(int, synonym)
            QueryEvaluator qe3Negative = QueryEvaluator();
            PKBMain PKB3Negative;
            expectedList1.clear();
            expectedList2.clear();
            expectedPair = getEmptyPairOfListOfString();
            actualPair = getEmptyPairOfListOfString();
            PKB3Negative.setFollowsRel(0, 1);
            PKB3Negative.setFollowsRel(1, 2);
            qe3Negative.setPkb(PKB3Negative);
            array<string, 4> arrToEvaluate3Negative = { "int", "2", "assign", "a" };
            qe3Negative.evaluateFollowsTest(arrToEvaluate3Negative);
            expectedPair = make_pair(expectedList1, expectedList2);
            actualPair = qe3Negative.getResultSuchThat();
            Assert::IsFalse(qe3Negative.getHasResult());
            Assert::IsTrue(expectedPair == actualPair);


            //Case 4 - Positive: Follows(_, int)
            //TODO

            //Case 4 - Negative: Follows(_, int)
            //TODO

            //Case 5 - Positive: Follows(_, _)
            //TODO

            //Case 5 - Negative: Follows(_, _)
            //TODO

            //Case 6 - Positive: Follows(_, synonym)
            //TODO

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
        }

        TEST_METHOD(TestEvaluateFollowsT)
        {

        }
        
        pair<list<string>, list<string>> getEmptyPairOfListOfString()
        {
            list<string> list1;
            list<string> list2;
            return make_pair(list1, list2);
        }
       

    };
}