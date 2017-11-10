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
        QueryTree *qtPtr;
        ClauseResult cr;
        ResultFormatter rf;

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            cr = ClauseResult();
            rf = ResultFormatter();
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

		TEST_METHOD(TestResultFormatter_SelectBOOLEAN_ClauseResultNonEmpty_True)
		{
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
			qtPtr->insertSelect(UtilitySelection::makeSelectClause(SELECT_BOOLEAN));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
			string synonym = "s";
			list<int> synonymResult = { 1,2,3 };
			cr.updateSynResults(synonym, synonymResult);
			Assert::IsTrue(rf.finalResultFromSelection(cr, *qtPtr).size()==1);
			Assert::IsTrue(rf.finalResultFromSelection(cr, *qtPtr).front()=="true");
		}
        
		TEST_METHOD(TestResultFormatter_SelectBOOLEAN_ClauseResultEmpty_False)
		{
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
			qtPtr->insertSelect(UtilitySelection::makeSelectClause(SELECT_BOOLEAN));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
			Assert::IsTrue(rf.handleNoResult(*qtPtr).size() == 1);
			Assert::IsTrue(rf.handleNoResult(*qtPtr).front() == "false");
		}

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultNonEmpty_OneResult_ResultExpected)
		{
			string synonym = "s";
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
			qtPtr->insertSelect(UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, synonym));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
			list<int> synonymResult = { 1,2,3 };
			cr.updateSynResults(synonym, synonymResult);
			Assert::IsTrue(cr.hasResults());			
			list<string> expectedResult = { "1","2","3" };
			list<string> actualResult = rf.finalResultFromSelection(cr, *qtPtr);
			Assert::IsTrue(actualResult.size() == 3);
		    Assert::IsTrue(actualResult == expectedResult);
		}

		TEST_METHOD(TestResultFormatter_SelectSynonym_ClauseResultNonEmpty_TwoResults_ResultExpected)
		{
			string synonym1 = "s1";
			string synonym2 = "s2";
			SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s1");
			qtPtr->insertSelect(UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, synonym1));
			Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qtPtr->getSelectClause()));
			list<int> synonym1Result = { 1,2 };
			list<int> synonym2Result = { 2,3, 4 };
			cr.updateSynResults(synonym1, synonym1Result);
			cr.updateSynResults(synonym2, synonym2Result);
			Assert::IsTrue(cr.hasResults());
			list<string> expectedResult = { "1","2" };
			list<string> actualResult = rf.finalResultFromSelection(cr, *qtPtr);
			Assert::IsTrue(actualResult.size() == 2);
			Assert::IsTrue(actualResult == expectedResult);
		}

	};
}
