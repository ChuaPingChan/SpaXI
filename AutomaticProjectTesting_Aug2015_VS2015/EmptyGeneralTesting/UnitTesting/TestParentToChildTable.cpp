#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/ParentToChildTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAdd)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			ParentToChildTable table;
			
			Assert::IsTrue(table.addParentChild(1, 2));
			Assert::IsTrue(table.addParentChild(1, 3));

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
		}

	};
}