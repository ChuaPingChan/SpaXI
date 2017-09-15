#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
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
			list<int> allBefore = PKB.getAllBefore("STMT");
			allBefore.sort();

			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 1) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 2) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 3) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 4) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 5) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 6) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 7) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 8) != allBefore.end());
			Assert::IsTrue(std::find(allBefore.begin(), allBefore.end(), 9) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 10) != allBefore.end());
			Assert::IsFalse(std::find(allBefore.begin(), allBefore.end(), 0) != allBefore.end());

			list<int> allAfter = PKB.getAllAfter("STMT");
			allAfter.sort();
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 1) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 2) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 3) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 4) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 5) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 6) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 7) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 8) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 9) != allAfter.end());
			Assert::IsTrue(std::find(allAfter.begin(), allAfter.end(), 10) != allAfter.end());
			Assert::IsFalse(std::find(allAfter.begin(), allAfter.end(), 0) != allAfter.end());

			Assert::IsTrue(PKB.hasFollows());

			Assert::IsTrue(PKB.isFollows(1, 2));
			Assert::IsTrue(PKB.isFollows(2, 3));
			Assert::IsTrue(PKB.isFollows(4, 5));
			Assert::IsTrue(PKB.isFollows(5, 6));
			Assert::IsTrue(PKB.isFollows(6, 8));
			Assert::IsTrue(PKB.isFollows(3, 9));
			Assert::IsTrue(PKB.isFollows(9, 10));

			pair<list<int>, list<int>> allFollows = PKB.getAllFollows();
			list<int> bef = allFollows.first;
			list<int> aft = allFollows.second;

			while (!bef.empty() && !aft.empty()) {
				Assert::IsTrue(PKB.isFollows(bef.front(), aft.front()));
				bef.pop_front();
				aft.pop_front();
			}
		}

		TEST_METHOD(TestPKBFollows2) 
		{
			PKBMain PKB;
			PKB.setFollowsRel(0, 1);

			Assert::IsFalse(PKB.hasFollows());
		}
	};
}
