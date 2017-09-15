#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestQueryTree)
    {
    public:
        QueryTree qt;

        TEST_METHOD(TestQueryTreeInitialisation)
        {
            qt = QueryTree();
            qt.init();
            Assert::IsTrue(qt.isInit());
            Assert::IsFalse(qt.isSplitted());
            Assert::IsFalse(qt.isValidated());
            Assert::IsFalse(qt.isEvaluated());
        }

        TEST_METHOD(TestStoreUnvalidatedStmts)
        {
            qt = QueryTree();
            vector<string> splitted;
            string expectedAssign = "assign a";
            string expectedStmt = "stmt s";
            string expectedVariable = "variable v";
            string expectedSelect = "Select s such that Uses(a, v)";
            splitted.push_back(expectedAssign);
            splitted.push_back(expectedStmt);
            splitted.push_back(expectedVariable);
            splitted.push_back(expectedSelect);
            qt.storeUnvalidatedStmts(splitted);

            vector<string> retrievedSplitted = qt.getUnvalidatedStmts();
            int counter = 0;
            for (vector<string>::iterator iter = retrievedSplitted.begin(); iter != retrievedSplitted.end(); ++iter) {
                string currentToken = *iter;
                if (counter == 0) {
                    Assert::AreEqual(expectedAssign, currentToken);
                }
                else if (counter == 1) {
                    Assert::AreEqual(expectedStmt, currentToken);
                }
                else if (counter == 2) {
                    Assert::AreEqual(expectedVariable, currentToken);
                }
                else if (counter == 3) {
                    Assert::AreEqual(expectedSelect, currentToken);
                }
                counter++;
            }
            
            Assert::IsTrue(qt.isSplitted());
        }

        TEST_METHOD(TestInsertVariableRetrieveVector)
        {
            qt = QueryTree();
            string synonymType;
            string synonym1;
            string synonym2;
            vector<string> retrievedList;

            synonymType = "stmt";
            synonym1 = "s1";
            synonym2 = "s2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getStmts();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);

            synonymType = "assign";
            synonym1 = "a1";
            synonym2 = "a2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getAssigns();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);

            synonymType = "while";
            synonym1 = "w1";
            synonym2 = "w2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getWhiles();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);

            synonymType = "variable";
            synonym1 = "v1";
            synonym2 = "v2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getVars();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);

            synonymType = "const";
            synonym1 = "c1";
            synonym2 = "c2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getConsts();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);

            synonymType = "prog_line";
            synonym1 = "p1";
            synonym2 = "p2";
            qt.insertVariable(synonymType, synonym1);
            qt.insertVariable(synonymType, synonym2);
            retrievedList = qt.getProgLines();
            checkInsertVariableRetrieveVector(synonym1, synonym2, retrievedList);
        }

        void checkInsertVariableRetrieveVector(string synonym1, string synonym2, vector<string> retrievedList) {
            int counter = 0;
            for (vector<string>::iterator iter = retrievedList.begin(); iter != retrievedList.end(); ++iter) {
                string currentToken = *iter;
                if (counter == 0) {
                    Assert::AreEqual(synonym1, currentToken);
                }
                else if (counter == 1) {
                    Assert::AreEqual(synonym2, currentToken);
                }
                
                counter++;
            }
        }

    };
}