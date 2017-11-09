#include "../stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/FollowsTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestAdd)
	{
	public:

		TEST_METHOD(TestAddRelations)
		{
			//Create ParentToChildTable
			FollowsTable table;

			//Test adding one parent child relation
			Assert::IsTrue(table.addFollows(1, 2));
			Assert::IsTrue(table.addFollows(2, 3));
			Assert::IsTrue(table.addFollows(3, 4));

		}
		
		TEST_METHOD(TestGetStmt)
		{
			FollowsTable table;
			Assert::IsTrue(table.addFollows(1, 2));
			Assert::IsTrue(table.addFollows(2, 3));
			Assert::IsTrue(table.addFollows(3, 4));

			Assert::AreEqual(table.getStmtAft(2), 3);
			Assert::AreEqual(table.getStmtBef(2), 1);

			Assert::AreEqual(table.getStmtAft(3), 4);
			Assert::AreEqual(table.getStmtBef(3), 2);
		}



	};
}