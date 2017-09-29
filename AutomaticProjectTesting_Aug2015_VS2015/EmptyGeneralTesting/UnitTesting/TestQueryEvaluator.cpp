//#include "stdafx.h"
//#include "CppUnitTest.h"
//#include "string.h"
//#include "..\SPA\PQL\QueryEvaluator.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTesting
//{
//    TEST_CLASS(TestQueryEvaluator)
//    {
//    public:
//        QueryEvaluator qe;
//
//        TEST_METHOD(TestEvaluateSelect)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluateFollows)
//        {
//            //Case1: int, int
//            qe = QueryEvaluator();
//
//        }
//
//        TEST_METHOD(TestEvaluateFollowsT)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluateParent)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluateParentT)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluateUses)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluateModifies)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestEvaluatePattern)
//        {
//            qe = QueryEvaluator();
//        }
//
//        TEST_METHOD(TestGetIntersection)
//        {
//            qe = QueryEvaluator();
//            list<string> list1;
//            list<string> list2;
//            list<string> expectedResult;
//            list<string> actualResult;
//
//            //Same item exist
//            list1.push_back("synonymHeader");
//            list1.push_back("var2");
//            list1.push_back("var2");
//            list1.push_back("var1");
//            list1.push_back("var3");
//            list1.push_back("var2");
//            list2.push_back("synonymHeader");
//            list2.push_back("var4");
//            list2.push_back("var2");
//            list2.push_back("var1");
//            list2.push_back("var3");
//            list2.push_back("var3");
//            list2.push_back("var5");
//            expectedResult.push_back("var1");
//            expectedResult.push_back("var2");
//            expectedResult.push_back("var3");
//            actualResult = qe.getIntersectionTest(list1, list2);
//            Assert::IsTrue(expectedResult == actualResult);
//
//            list1.clear();
//            list2.clear();
//            expectedResult.clear();
//            actualResult.clear();
//
//            //No same item exist
//            list1.push_back("synonymHeader");
//            list1.push_back("var7");
//            list1.push_back("var2");
//            list1.push_back("var1");
//            list1.push_back("var3");
//            list1.push_back("var224");
//            list2.push_back("synonymHeader");
//            list2.push_back("var76");
//            list2.push_back("var42");
//            list2.push_back("var10");
//            list2.push_back("var323");
//            list2.push_back("var533");
//            list2.push_back("var15");
//            
//            actualResult = qe.getIntersectionTest(list1, list2);
//            Assert::IsTrue(expectedResult == actualResult);
//        }
//
//    };
//}