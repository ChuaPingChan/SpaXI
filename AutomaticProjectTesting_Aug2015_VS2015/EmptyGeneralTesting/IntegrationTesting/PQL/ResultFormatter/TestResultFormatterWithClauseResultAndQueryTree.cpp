#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\ResultFormatter\ResultFormatter.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\Utility\UtilityQueryTree.h"
#include "..\SPA\PQL\Utilities\ClauseResult.h"
#include "..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
	TEST_CLASS(TestResultFormatterWithClauseResultAndQueryTree)
	{
	public:

		TEST_METHOD(TestResultFormatter_SelectionBoolean_ClauseResultNonEmpty_True)
		{
			QueryTree qt;
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_BOOLEAN));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			string synonym = "s";
			list<int> synonymResult = { 1,2,3 };
			ClauseResult cr;
			cr.updateSynResults(synonym, synonymResult);
			ResultFormatter rf;
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).front()=="TRUE");
		}

		TEST_METHOD(TestResultFormatter_SelectionBoolean_ClauseResultEmpty_False)
		{
			QueryTree qt;
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_BOOLEAN));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			ClauseResult cr;
			ResultFormatter rf;
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).front() == "FALSE");
		}

	};
}
