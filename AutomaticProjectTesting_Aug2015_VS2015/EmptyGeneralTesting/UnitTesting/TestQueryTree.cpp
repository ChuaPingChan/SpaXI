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
            
			Assert::IsTrue(splitted.size() == 4);
        }

        //TEST_METHOD(TestInsertSelect)

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

        TEST_METHOD(TestInsertFollowsRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s1";
            string arg2Type = "stmt";
            string arg2 = "s2";
            array<string, 4> newFollowsArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertFollows(newFollowsArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getFollows(), 0);

            arg1Type = "assign";
            arg1 = "a1";
            arg2Type = "assign";
            arg2 = "a2";
            newFollowsArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertFollows(newFollowsArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getFollows(), 1);
        }

        TEST_METHOD(TestInsertFollowsStarRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s1";
            string arg2Type = "stmt";
            string arg2 = "s2";
            array<string, 4> newFollowsStarArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertFollowsStar(newFollowsStarArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getFollowsT(), 0);

            arg1Type = "assign";
            arg1 = "a1";
            arg2Type = "assign";
            arg2 = "a2";
            newFollowsStarArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertFollowsStar(newFollowsStarArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getFollowsT(), 1);
        }

        TEST_METHOD(TestInsertParentRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s1";
            string arg2Type = "stmt";
            string arg2 = "s2";
            array<string, 4> newParentArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertParent(newParentArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getParent(), 0);

            arg1Type = "while";
            arg1 = "w1";
            arg2Type = "while";
            arg2 = "w2";
            newParentArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertParent(newParentArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getParent(), 1);
        }

        TEST_METHOD(TestInsertParentStarRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s1";
            string arg2Type = "stmt";
            string arg2 = "s2";
            array<string, 4> newParentStarArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertParentStar(newParentStarArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getParentT(), 0);

            arg1Type = "assign";
            arg1 = "a1";
            arg2Type = "assign";
            arg2 = "a2";
            newParentStarArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertParentStar(newParentStarArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getParentT(), 1);
        }

        TEST_METHOD(TestInsertUsesRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s";
            string arg2Type = "variable";
            string arg2 = "v";
            array<string, 4> newUsesArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertUses(newUsesArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getUses(), 0);

            arg1Type = "while";
            arg1 = "w";
            arg2Type = "variable";
            arg2 = "v";
            newUsesArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertUses(newUsesArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getUses(), 1);
        }

        TEST_METHOD(TestInsertModifiesRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "stmt";
            string arg1 = "s";
            string arg2Type = "variable";
            string arg2 = "v";
            array<string, 4> newModifiesArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertModifies(newModifiesArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getModifies(), 0);

            arg1Type = "while";
            arg1 = "w";
            arg2Type = "variable";
            arg2 = "v";
            newModifiesArray = { arg1Type, arg1, arg2Type, arg2 };
            qt.insertModifies(newModifiesArray);
            checkInsertRelationshipRetrieveVector(arg1Type, arg1, arg2Type, arg2, qt.getModifies(), 1);
        }

        TEST_METHOD(TestInsertPatternRetrieveVector)
        {
            qt = QueryTree();
            string arg1Type = "assign";
            string arg1 = "a1";
            string arg2Type = "variable";
            string arg2 = "v1";
            string arg3Type = "_";
            string arg3 = "";
            array<string, 6> newPatternArray = { arg1Type, arg1, arg2Type, arg2, arg3Type, arg3 };
            qt.insertPattern(newPatternArray);
            checkInsertPatternRetrieveVector(arg1Type, arg1, arg2Type, arg2, arg3Type, arg3, qt.getPatterns(), 0);

            arg1Type = "assign";
            arg1 = "a2";
            arg2Type = "variable";
            arg2 = "v2";
            arg3Type = "_";
            arg3 = "";
            newPatternArray = { arg1Type, arg1, arg2Type, arg2, arg3Type, arg3 };
            qt.insertPattern(newPatternArray);
            checkInsertPatternRetrieveVector(arg1Type, arg1, arg2Type, arg2, arg3Type, arg3, qt.getPatterns(), 1);
        }

        void checkInsertRelationshipRetrieveVector(string arg1Type, string arg1, string arg2Type, string arg2, vector<array<string, 4>> retrievedVectorFromTree, int index)
        {
            array<string, 4> fromTreeArray = retrievedVectorFromTree.at(index);
            Assert::AreEqual(arg1Type, fromTreeArray[0]);
            Assert::AreEqual(arg1, fromTreeArray[1]);
            Assert::AreEqual(arg2Type, fromTreeArray[2]);
            Assert::AreEqual(arg2, fromTreeArray[3]);
        }

        void checkInsertPatternRetrieveVector(string arg1Type, string arg1, string arg2Type, string arg2, string arg3Type, string arg3, vector<array<string, 6>> retrievedVectorFromTree, int index)
        {
            array<string, 6> fromTreeArray = retrievedVectorFromTree.at(index);
            Assert::AreEqual(arg1Type, fromTreeArray[0]);
            Assert::AreEqual(arg1, fromTreeArray[1]);
            Assert::AreEqual(arg2Type, fromTreeArray[2]);
            Assert::AreEqual(arg2, fromTreeArray[3]);
            Assert::AreEqual(arg3Type, fromTreeArray[4]);
            Assert::AreEqual(arg3, fromTreeArray[5]);
        }

    };
}