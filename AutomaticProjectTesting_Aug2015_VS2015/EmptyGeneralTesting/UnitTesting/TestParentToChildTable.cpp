#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/ParentToChildTable.h"
#include "../SPA/PKB/ChildToParentTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAdd)
	{
	public:

		TEST_METHOD(TestAddRelations)
		{
			//Create ParentToChildTable
			ParentToChildTable table;

			//Test adding one parent child relation
			Assert::IsTrue(table.addParentChild(1, 2));
			//Test adding another parent child relation
			Assert::IsTrue(table.addParentChild(2, 3));
			//Test adding to same parent
			Assert::IsTrue(table.addParentChild(2, 4));

			//Create ChildToParentTable
			ChildToParentTable ctpt;
			Assert::IsTrue(ctpt.addChildParent(1, 2));

			Assert::IsTrue(ctpt.getParent(1) == 0);
			//TODO 4 check if invalid returns 0 and how PKBMain deals with it
		}

		TEST_METHOD(TestMultipleChildren)
		{
			// TODO: Your test code here
			ParentToChildTable table;
			
			Assert::IsTrue(table.addParentChild(1, 2));
			Assert::IsTrue(table.addParentChild(1, 3));

			Assert::IsTrue(table.isParentChild(1, 2));
			Assert::IsTrue(table.isParentChild(1, 3));
			
			list<int> temp;
			list<int> childrenList;
			temp.push_back(2);
			temp.push_back(3);
			childrenList = table.getChildren(1);
			while (!temp.empty() && !table.getChildren(1).empty()) {
				Assert::AreEqual(childrenList.front(), temp.front());
				childrenList.pop_front();
				temp.pop_front();
			};

			//Add duplicate relation
			Assert::IsTrue(table.addParentChild(1, 2));
			childrenList = table.getChildren(1);
			//Checks that the values are unique
			while (!temp.empty() && !table.getChildren(1).empty()) {
				Assert::AreEqual(childrenList.front(), temp.front());
				childrenList.pop_front();
				temp.pop_front();
			};
		}



	};
}