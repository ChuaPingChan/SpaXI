#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/PKB/PKBMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestPKBMain)
	{
	public:

		TEST_METHOD(TestPKBFollows)
		{
			PKBMain PKB;

			PKB.setFollowsRel(0, 1);
			PKB.setFollowsRel(1, 2);
			PKB.setFollowsRel(2, 3);
			PKB.setFollowsRel(0, 4);
			PKB.setFollowsRel(4, 5);
			PKB.setFollowsRel(5, 6);
			PKB.setFollowsRel(0, 7);
			PKB.setFollowsRel(6, 8);
			PKB.setFollowsRel(3, 9);
			PKB.setFollowsRel(9, 10);

			Assert::AreEqual(PKB.getAfter(1), 2);
			Assert::AreEqual(PKB.getAfter(10), 0);
		}
	};
}
