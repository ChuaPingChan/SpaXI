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
			Assert::IsTrue(rf.handleNoResult(qt).size() == 1);
			Assert::IsTrue(rf.handleNoResult(qt).front() == "false");
		}

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultNonEmpty_OneResult_ResultExpected)
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

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultNonEmpty_TwoResults_ResultExpected)
		{
			QueryTree qt;
			string synonym1 = "s1";
			string synonym2 = "s2";
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s1");
			qt.insertSelect(UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, synonym1));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
			list<int> synonym1Result = { 1,2 };
			list<int> synonym2Result = { 2,3, 4 };
			ClauseResult cr;
			cr.updateSynResults(synonym1, synonym1Result);
			cr.updateSynResults(synonym2, synonym2Result);
			Assert::IsTrue(cr.hasResults());
			list<string> expectedResult = { "1","2" };
			ResultFormatter rf;
			list<string> actualResult = rf.finalResultFromSelection(cr, qt);
			Assert::IsTrue(actualResult.size() == 2);
			Assert::IsTrue(actualResult == expectedResult);
		}

	};
}
