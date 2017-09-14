#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/DesignExtractor.h"
#include "../SPA/PKB/ParentToChildTable.h"
#include "../SPA/PKB/ParentToChildStarTable.h"
#include "../SPA/PKB/ChildToParentStarTable.h"

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
			
			Assert::IsTrue(ptcst.isParentStar(3, 4));

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



	};
}