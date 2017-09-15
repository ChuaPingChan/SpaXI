#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/DesignExtractor.h"
#include "../SPA/PKB/ParentToChildTable.h"
#include "../SPA/PKB/ParentToChildStarTable.h"
#include "../SPA/PKB/ChildToParentStarTable.h"
#include "../SPA/PKB/FollowsStarAfter.h"
#include "../SPA/PKB/FollowsStarBefore.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestParentStar)
	{
	public:

		TEST_METHOD(TestGenerateParentStar)
		{
			DesignExtractor de;
			ParentToChildTable ptct;
			ptct.addParentChild(1, 2);
			ptct.addParentChild(1, 3);
			ptct.addParentChild(3, 4);
			ptct.addParentChild(3, 5);

			unordered_map<int, list<int>> ptcsm = de.computeParentToChildStarTable(ptct);

			ParentToChildStarTable ptcst;
			ptcst.setMap(ptcsm);
			
			list<int> children;
			children = ptcst.getChildren(1);
			
			Assert::IsTrue(ptcst.isParentStarChild(1, 2));
			Assert::IsTrue(ptcst.isParentStarChild(1, 3));
			Assert::IsTrue(ptcst.isParentStarChild(1, 4));
			Assert::IsTrue(ptcst.isParentStarChild(1, 5));

			list<int> testChildren;
			testChildren.push_back(2);
			testChildren.push_back(3);
			testChildren.push_back(4);
			testChildren.push_back(5);

			Assert::IsTrue(testChildren == children);

			list<int> testChildren2;
			testChildren2.push_back(4);
			testChildren2.push_back(5);
			
			Assert::IsTrue(ptcst.isParentStarChild(3, 4));

			Assert::IsTrue(testChildren2 == ptcst.getChildren(3));
		}

		TEST_METHOD(TestGenerateChildrenStar)
		{
			DesignExtractor de;
			ChildToParentTable ctpt;
			ctpt.addChildParent(2, 1);
			ctpt.addChildParent(3, 1);
			ctpt.addChildParent(4, 3);
			ctpt.addChildParent(5, 3);

			ChildToParentStarTable ctpst;
			ctpst.setMap(de.computeChildToParentStarTable(ctpt));

			Assert::IsTrue(ctpst.isParentStar(1, 2));
			Assert::IsTrue(ctpst.isParentStar(1, 3));
			Assert::IsTrue(ctpst.isParentStar(1, 4));
			Assert::IsTrue(ctpst.isParentStar(1, 5));
		}

		TEST_METHOD(TestGenerateFollowsAfterStar)
		{
			DesignExtractor de;
			FollowsTable ft;

			ft.addFollows(1, 0, 2);
			ft.addFollows(2, 1, 3);
			ft.addFollows(3, 2, 9);
			ft.addFollows(4, 0, 5);
			ft.addFollows(5, 4, 6);
			ft.addFollows(6, 5, 8);
			ft.addFollows(7, 0, 0);
			ft.addFollows(8, 6, 0);
			ft.addFollows(9, 3, 10);
			ft.addFollows(10, 9, 0);

			FollowsStarAfter fsa;
			fsa.setMap(de.computeFollowsStarAfterTable(ft));

			Assert::IsTrue(fsa.isAfterStar(1, 2));
			Assert::IsTrue(fsa.isAfterStar(1, 3));
			Assert::IsTrue(fsa.isAfterStar(1, 9));
			Assert::IsTrue(fsa.isAfterStar(1, 10));
			Assert::IsTrue(fsa.isAfterStar(2, 3));
			Assert::IsTrue(fsa.isAfterStar(2, 9));
			Assert::IsTrue(fsa.isAfterStar(2, 10));
			Assert::IsTrue(fsa.isAfterStar(3, 9));
			Assert::IsTrue(fsa.isAfterStar(3, 10));
			Assert::IsTrue(fsa.isAfterStar(4, 5));
			Assert::IsTrue(fsa.isAfterStar(4, 6));
			Assert::IsTrue(fsa.isAfterStar(5, 6));
			Assert::IsTrue(fsa.isAfterStar(9, 10));
			Assert::IsFalse(fsa.isAfterStar(8, 10));
			Assert::IsFalse(fsa.isAfterStar(1, 8));

			list<int> temp;
			temp.push_back(2);
			temp.push_back(3);
			temp.push_back(9);
			temp.push_back(10);

			Assert::IsTrue(temp == fsa.getAfterStar(1));

			list<int> temp2;
			temp2.push_back(5);
			temp2.push_back(6);
			temp2.push_back(8);
			Assert::IsTrue(temp2 == fsa.getAfterStar(4));

			FollowsStarBefore fsb;
			fsb.setMap(de.computeFollowsStarBeforeTable(ft));

			Assert::IsTrue(fsb.isBeforeStar(1, 2));
			Assert::IsTrue(fsb.isBeforeStar(1, 3));
			Assert::IsTrue(fsb.isBeforeStar(1, 9));
			Assert::IsTrue(fsb.isBeforeStar(1, 10));
			Assert::IsTrue(fsb.isBeforeStar(2, 3));
			Assert::IsTrue(fsb.isBeforeStar(2, 9));
			Assert::IsTrue(fsb.isBeforeStar(2, 10));
			Assert::IsTrue(fsb.isBeforeStar(3, 9));
			Assert::IsTrue(fsb.isBeforeStar(3, 10));
			Assert::IsTrue(fsb.isBeforeStar(4, 5));
			Assert::IsTrue(fsb.isBeforeStar(4, 6));
			Assert::IsTrue(fsb.isBeforeStar(5, 6));
			Assert::IsTrue(fsb.isBeforeStar(9, 10));
			Assert::IsFalse(fsb.isBeforeStar(8, 10));
			Assert::IsFalse(fsb.isBeforeStar(1, 8));
		}

	};
}