#include "../stdafx.h"
#include "CppUnitTest.h"
#include "../../SPA/PKB/Cache.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestCache)
	{
	public:
		TEST_METHOD(TestAddNextStar) {
			Cache cache;
			list<int> beforeList = { 1, 2 };
			list<int> afterList = { 3, 4 };
			cache.putAllNextStar(make_pair(beforeList, afterList), STMT, STMT);
			Assert::IsTrue(cache.containsAllNextStar(STMT, STMT));
			Assert::IsTrue(cache.getAllNextStar(STMT, STMT) == make_pair(beforeList, afterList));
		}

		TEST_METHOD(TestAddAffectsStar) {
			Cache cache;
			list<int> beforeList = { 1, 2 };
			list<int> afterList = { 3, 4 };
			unordered_map<int, unordered_set<int>> affectsRelMap;
			affectsRelMap[1].insert(3);
			affectsRelMap[2].insert(4);
			cache.putAllAffects(make_pair(beforeList, afterList), affectsRelMap);
			Assert::IsTrue(cache.containsAllAffects());
			Assert::IsTrue(cache.getAllAffects() == make_pair(beforeList, afterList));
		}
	};
}