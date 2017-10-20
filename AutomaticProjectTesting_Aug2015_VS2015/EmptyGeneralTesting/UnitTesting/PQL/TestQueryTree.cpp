#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestQueryTree)
    {
        unordered_set<string> expectedSet;
        unordered_set<string> actualSet;

    public:

        TEST_METHOD_INITIALIZE(TestMethodInitialize)
        {
            expectedSet.clear();
            actualSet.clear();
        }

        TEST_METHOD_CLEANUP(TestMethodCleanup)
        {
            expectedSet.clear();
            actualSet.clear();
        }

        bool isSameContent(SuchThatClause expected, SuchThatClause actual)
        {
            return expected.getRel() == actual.getRel()
                && expected.getArgOneType() == actual.getArgOneType()
                && expected.getArgTwoType() == actual.getArgTwoType()
                && expected.getArgOne() == actual.getArgOne()
                && expected.getArgTwo() == actual.getArgTwo();
        }

        TEST_METHOD(TestTree_InsertStmt_RetrieveStmt_Once_Valid)
        {
            QueryTree qt = QueryTree();
            qt.insertSynonym(STMT, "s");
            expectedSet.insert("s");
            actualSet = qt.getStmts();
            Assert::IsTrue(expectedSet == actualSet);
        }

        TEST_METHOD(TestTree_InsertStmt_RetrieveStmt_Multiple_Valid)
        {
            QueryTree qt = QueryTree();
            qt.insertSynonym(STMT, "s1");
            qt.insertSynonym(STMT, "s2");
            qt.insertSynonym(STMT, "s3");
            expectedSet.insert("s1");
            expectedSet.insert("s2");
            expectedSet.insert("s3");
            actualSet = qt.getStmts();
            Assert::IsTrue(expectedSet == actualSet);
        }

        TEST_METHOD(TestTree_InsertSelectBoolean_RetrieveSelect_Valid)
        {
            QueryTree qt = QueryTree();
            SelectClause expectedSc = SelectClause(SELECT_BOOLEAN);
            qt.insertSelect(expectedSc);
            SelectClause actualSc = qt.getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
        }

        TEST_METHOD(TestTree_InsertSelectSingle_RetrieveSelect_Valid)
        {
            QueryTree qt = QueryTree();
            SelectClause expectedSc = SelectClause(SELECT_SINGLE, ASSIGN, "a");
            qt.insertSelect(expectedSc);
            SelectClause actualSc = qt.getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
            Assert::IsTrue(expectedSc.getSingleArgType() == actualSc.getSingleArgType());
        }

        TEST_METHOD(TestTree_InsertSelectTuple_RetrieveSelect_Valid)
        {
            QueryTree qt = QueryTree();
            vector<Entity> expectedEntityVector;
            expectedEntityVector.push_back(ASSIGN);
            vector<string> expectedSynonymVector;
            expectedSynonymVector.push_back("a");
            SelectClause expectedSc = SelectClause(SELECT_TUPLE, expectedEntityVector, expectedSynonymVector);
            qt.insertSelect(expectedSc);
            SelectClause actualSc = qt.getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
            Assert::IsTrue(expectedSc.getTupleArgTypes() == actualSc.getTupleArgTypes());
            Assert::IsTrue(expectedSc.getTupleArgs() == actualSc.getTupleArgs());
        }

        /*TEST_METHOD(TestTree_InsertSuchThatClause_RetrieveSuchThatClause_Valid)
        {
            QueryTree qt = QueryTree();
            SuchThatClause expectedStc = SuchThatClause(MODIFIES, STMT, "s", VARIABLE, "v");
            qt.insertSuchThat(expectedStc);
            SuchThatClause actualSc = qt.getSuchThatClauses();
            Assert::IsTrue(expectedStc.getSelectionType() == actualSc.getSelectionType());
            Assert::IsTrue(expectedStc.getSingleArgType() == actualSc.getSingleArgType());
        }*/
        
    };
}
