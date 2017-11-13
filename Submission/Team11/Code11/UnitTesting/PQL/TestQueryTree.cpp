#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestQueryTree)
    {
        QueryTree *qtPtr;
        unordered_set<string> expectedSet;
        unordered_set<string> actualSet;

    public:

        TEST_METHOD_INITIALIZE(TestMethodInitialize)
        {
            qtPtr = new QueryTree();
            expectedSet.clear();
            actualSet.clear();
        }

        TEST_METHOD_CLEANUP(TestMethodCleanup)
        {
            delete qtPtr;
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
            qtPtr->insertSynonym(STMT, "s");
            expectedSet.insert("s");
            actualSet = qtPtr->getStmts();
            Assert::IsTrue(expectedSet == actualSet);
        }

        TEST_METHOD(TestTree_InsertStmt_RetrieveStmt_Multiple_Valid)
        {
            qtPtr->insertSynonym(STMT, "s1");
            qtPtr->insertSynonym(STMT, "s2");
            qtPtr->insertSynonym(STMT, "s3");
            expectedSet.insert("s1");
            expectedSet.insert("s2");
            expectedSet.insert("s3");
            actualSet = qtPtr->getStmts();
            Assert::IsTrue(expectedSet == actualSet);
        }

        TEST_METHOD(TestTree_InsertSelectBoolean_RetrieveSelect_Valid)
        {
            SelectClause expectedSc = SelectClause(SELECT_BOOLEAN);
            qtPtr->insertSelect(expectedSc);
            SelectClause actualSc = qtPtr->getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
        }

        TEST_METHOD(TestTree_InsertSelectSingle_RetrieveSelect_Valid)
        {
            SelectClause expectedSc = SelectClause(SELECT_SINGLE, ASSIGN, "a");
            qtPtr->insertSelect(expectedSc);
            SelectClause actualSc = qtPtr->getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
            Assert::IsTrue(expectedSc.getSingleArgType() == actualSc.getSingleArgType());
        }

        TEST_METHOD(TestTree_InsertSelectTuple_RetrieveSelect_Valid)
        {
            vector<Entity> expectedEntityVector;
            expectedEntityVector.push_back(ASSIGN);
            vector<string> expectedSynonymVector;
            expectedSynonymVector.push_back("a");
            SelectClause expectedSc = SelectClause(SELECT_TUPLE, expectedEntityVector, expectedSynonymVector);
            qtPtr->insertSelect(expectedSc);
            SelectClause actualSc = qtPtr->getSelectClause();
            Assert::IsTrue(expectedSc.getSelectionType() == actualSc.getSelectionType());
            Assert::IsTrue(expectedSc.getTupleArgTypes() == actualSc.getTupleArgTypes());
            Assert::IsTrue(expectedSc.getTupleArgs() == actualSc.getTupleArgs());
        }
    };
}
