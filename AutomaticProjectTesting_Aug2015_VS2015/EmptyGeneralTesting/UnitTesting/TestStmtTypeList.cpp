#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SPA\PKB\StmtTypeList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestStmtTypeList)
    {
    public:
        TEST_METHOD(TestAssign)
        {
            StmtTypeList assignList;

            Assert::IsTrue(assignList.addToAssignStmtList(1));
            Assert::IsTrue(assignList.addToAssignStmtList(2));
            Assert::IsTrue(assignList.addToAssignStmtList(5));
            Assert::IsTrue(assignList.addToAssignStmtList(7));

            Assert::IsTrue(assignList.isAssignStmt(1));
            Assert::IsTrue(assignList.isAssignStmt(7));
            Assert::IsFalse(assignList.isAssignStmt(4));
        }
        TEST_METHOD(TestWhile)
        {
            StmtTypeList whileList;

            Assert::IsTrue(whileList.addToWhileStmtList(4));
            Assert::IsTrue(whileList.addToWhileStmtList(6));
            Assert::IsTrue(whileList.addToWhileStmtList(8));

            Assert::IsTrue(whileList.isWhileStmt(4));
            Assert::IsFalse(whileList.isWhileStmt(7));
        }
        TEST_METHOD(TestPresent)
        {
            StmtTypeList list;
            Assert::IsTrue(list.addToAssignStmtList(1));
            Assert::IsTrue(list.addToAssignStmtList(2));
            Assert::IsTrue(list.addToAssignStmtList(5));
            Assert::IsTrue(list.addToAssignStmtList(7));
            Assert::IsTrue(list.addToAssignStmtList(3));
            Assert::IsTrue(list.addToWhileStmtList(4));
            Assert::IsTrue(list.addToWhileStmtList(6));
            Assert::IsTrue(list.addToWhileStmtList(8));

            Assert::IsTrue(list.isPresent(8));
            Assert::IsFalse(list.isPresent(9));
        }

    };
}