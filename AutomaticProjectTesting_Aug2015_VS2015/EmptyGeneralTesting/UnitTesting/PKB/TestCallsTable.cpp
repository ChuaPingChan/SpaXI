#include "../stdafx.h"
#include "CppUnitTest.h"
#include "../../SPA/PKB/CallsTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestCallsTable)
	{
	public:
		TEST_METHOD(TestAdd) {
			CallsTable ct;
			Assert::IsTrue(ct.addCallsRel(1, 2));
			Assert::IsTrue(ct.addCallsStmt(3, 2));
		}

		TEST_METHOD(TestRelations) {
			CallsTable ct;
			Assert::IsTrue(ct.addCallsRel(1, 2));
			Assert::IsTrue(ct.addCallsRel(2, 3));
			Assert::IsTrue(ct.addCallsStmt(3, 2));
			Assert::IsTrue(ct.isCalls(1, 2));

			list<int> expectedCallers;
			expectedCallers.push_back(1);
			expectedCallers.push_back(2);
			Assert::IsTrue(ct.getAllCallers() == expectedCallers);
		}
	};
}