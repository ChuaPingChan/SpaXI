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
       // TEST_METHOD(TestEvaluatorSelect)
       // {
            
       // }

        TEST_METHOD(TestEvaluatorFollows)
        {
            //Case 1 - Positive: Follows(int, int)
            /*QueryEvaluator qe1Positive = QueryEvaluator();
            PKBMain PKB1Positive;
            PKB1Positive.setFollowsRel(1, 2);
            qe1Positive.setPkb(PKB1Positive);
            array<string, 4> arrToEvaluate1Positive = { "int", "1", "int", "2" };
            qe1Positive.evaluateFollowsTest(arrToEvaluate1Positive);
            Assert::IsTrue(qe1Positive.getHasResult());*/

            //Case 1 - Negative: Follows(int, int)
            /*QueryEvaluator qe1Negative = QueryEvaluator();
            PKBMain PKB1Negative;
            PKB1Negative.setFollowsRel(1, 2);
            qe1Negative.setPkb(PKB1Negative);
            array<string, 4> arrToEvaluate1Negative = { "int", "3", "int", "4" };
            qe1Negative.evaluateFollowsTest(arrToEvaluate1Negative);
            Assert::IsFalse(qe1Negative.getHasResult());*/

            //Case 2 - Positive: Follows(int, _)
            /*QueryEvaluator qe2Positive = QueryEvaluator();
            PKBMain PKB2Positive;
            PKB2Positive.setFollowsRel(1, 2);
            qe2Positive.setPkb(PKB2Positive);
            array<string, 4> arrToEvaluate2Positive = { "int", "1", "_", "" };
            qe2Positive.evaluateFollowsTest(arrToEvaluate2Positive);
            Assert::IsTrue(qe2Positive.getHasResult());*/

            //Case 2 - Negative: Follows(int, _)
            /*QueryEvaluator qe2Negative = QueryEvaluator();
            PKBMain PKB2Negative;
            PKB2Negative.setFollowsRel(1, 2);
            qe2Negative.setPkb(PKB2Negative);
            array<string, 4> arrToEvaluate2Negative = { "int", "3", "_", "" };
            qe2Negative.evaluateFollowsTest(arrToEvaluate2Negative);
            Assert::IsFalse(qe2Negative.getHasResult());*/
        }

        TEST_METHOD(TestEvaluateFollowsT)
        {

        }
        

       

    };
}