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

		TEST_METHOD(TestResultFormatter_SelectBOOLEAN_ClauseResultNonEmpty_True)
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
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).size()==1);
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).front()=="true");
		}

		TEST_METHOD(TestResultFormatter_SelectBOOLEAN_ClauseResultEmpty_False)
		{
			QueryTree qt;
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_BOOLEAN));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			ClauseResult cr;
			ResultFormatter rf;
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).size() == 1);
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).front() == "false");
		}

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultEmpty_NoResult_EmptyString)
		{
			QueryTree qt;
			string synonym = "s";
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_SINGLE,STMT,synonym));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			ClauseResult cr;
			ResultFormatter rf;
			Assert::IsTrue(rf.finalResultFromSelection(cr, qt).empty());
		}

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultNonEmpty_ResultExpected)
		{
			QueryTree qt;
			string synonym = "s";
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, synonym));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			list<int> synonymResult = { 1,2,3 };
			ClauseResult cr;
			cr.updateSynResults(synonym, synonymResult);
			Assert::IsTrue(cr.hasResults());			
			list<string> expectedResult = { "1","2","3" };
			ResultFormatter rf;
			list<string> actualResult = rf.finalResultFromSelection(cr, qt);
			Assert::IsTrue(actualResult.size() == 3);
		    Assert::IsTrue(actualResult == expectedResult);
		}

	};
}
