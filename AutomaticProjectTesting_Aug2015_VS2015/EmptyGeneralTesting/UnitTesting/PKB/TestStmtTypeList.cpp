#include "../stdafx.h"
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
            Assert::IsTrue(list.addToIfStmtList(9));

            Assert::IsTrue(list.isPresent(9));
            Assert::IsFalse(list.isPresent(10));
        }
        TEST_METHOD(TestIfElse)
        {
            StmtTypeList list;
            Assert::IsTrue(list.addToIfStmtList(1));
            Assert::IsTrue(list.addToIfStmtList(4));
            Assert::IsTrue(list.addToIfStmtList(7));
            Assert::IsTrue(list.addToIfStmtList(10));

            Assert::IsTrue(list.isIfStmt(7));
            Assert::IsFalse(list.isIfStmt(8));
        }
    };
}