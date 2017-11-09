#include <string>
#include <cstdio>
#include <regex>

#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"
#include "../SPA/PKB/PKBMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestParserPopulatePkb)
    {
    public:

        const std::string dummySimpleSourcePath = "../UnitTesting/ParserTestDependencies/dummySimpleSource.txt";
        PKBMain pkb;   // Purposely construct new PKB (non-singleton)
        PKBMain* pkbPtr = &pkb;

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_equalSignMissing)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingEqual());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_missingSemicolon)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingSemicolon());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_wrongProcName)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_wrongProcName());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_whileOnly_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_whileOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_nonNextedIfElse_success)
        {
            // Set up
            list<string> actualStringResults;
            list<string> expectedStringResults;
            list<int> actualIntResults;
            list<int> expectedIntResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_nonNestedIfElse());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Test adding of if-else statements
            actualIntResults = pkb.getAllIfs();
            expectedIntResults = list<int>{ 4, 10 };
            actualIntResults.sort();
            expectedIntResults.sort();
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Test if parents are updated correctly
            actualIntResults = pkb.getAllParents(Entity::STMT);
            expectedIntResults = list<int>{ 4, 10 };
            actualIntResults.sort();
            expectedIntResults.sort();
            Assert::IsTrue(actualIntResults == expectedIntResults);

            actualIntResults = pkb.getAllParents(Entity::IF);
            expectedIntResults = list<int>{ 4, 10 };
            actualIntResults.sort();
            expectedIntResults.sort();
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Test if children are updated correctly
            actualIntResults = pkb.getAllChildren(Entity::STMT);
            expectedIntResults = list<int>{ 5, 6, 7, 8, 11, 12, 13 };
            actualIntResults.sort();
            expectedIntResults.sort();
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile2_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile2());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_missingBoolVar)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile_missingBoolVar());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd2LevelNestedWhile_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_2LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAddStmtsOfProc)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_iteration3complexity());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            int actualIntResult;
            list<string> actualStrResults;
            list<string> expectedStrResults;

            expectedStrResults = list<string>{ "ABC" };
            actualIntResult = pkb.getProcFromStmt(4);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(10);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(14);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(20);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);

            expectedStrResults = list<string>{ "GHI" };
            actualIntResult = pkb.getProcFromStmt(40);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(61);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(41);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);
            actualIntResult = pkb.getProcFromStmt(52);
            actualStrResults = pkb.convertIdxToString(list<int>{actualIntResult}, Entity::PROCEDURE);
            Assert::IsTrue(actualStrResults == expectedStrResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(simpleNextRelation)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_simpleNextRelation1());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Test if all if-else statements are added correctly
            actualResults = pkb.getAllIfs();
            expectedResults = list<int>{ 5 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Test if all while statements are added correctly
            actualResults = pkb.getAllWhiles();
            expectedResults = list<int>{ 3 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            Assert::IsTrue(pkb.isNext(1, 2));
            Assert::IsTrue(pkb.isNext(2, 3));
            Assert::IsTrue(pkb.isNext(3, 4));
            Assert::IsTrue(pkb.isNext(4, 5));

            Assert::IsTrue(pkb.isNext(5, 7));
            Assert::IsTrue(pkb.isNext(6, 8));
            Assert::IsTrue(pkb.isNext(7, 8));
            Assert::IsTrue(pkb.isNext(8, 3));
            Assert::IsTrue(pkb.isNext(3, 9));

            Assert::IsFalse(pkb.isNext(8, 9));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestNextRelation)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_comprehensiveNextRelations());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Simple Next relations
            Assert::IsTrue(pkb.isNext(1, 2));
            Assert::IsTrue(pkb.isNext(2, 3));
            Assert::IsTrue(pkb.isNext(7, 8));
            Assert::IsTrue(pkb.isNext(74, 75));

            // Next relations when entering if-block
            Assert::IsTrue(pkb.isNext(4, 5));
            Assert::IsTrue(pkb.isNext(16, 17));
            Assert::IsTrue(pkb.isNext(19, 20));
            Assert::IsTrue(pkb.isNext(67, 68));

            // Next relations when entering else-block
            Assert::IsTrue(pkb.isNext(4, 6));
            Assert::IsTrue(pkb.isNext(16, 18));
            Assert::IsTrue(pkb.isNext(19, 21));

            // Next relations when entering while-block
            Assert::IsTrue(pkb.isNext(3, 4));
            Assert::IsTrue(pkb.isNext(27, 28));
            Assert::IsTrue(pkb.isNext(45, 46));

            // Next relations across while-block
            Assert::IsTrue(pkb.isNext(8, 14));
            Assert::IsTrue(pkb.isNext(38, 41));

            // Next relations when exiting ifElse-block or while-block
            Assert::IsTrue(pkb.isNext(5, 3));
            Assert::IsTrue(pkb.isNext(6, 3));
            Assert::IsTrue(pkb.isNext(11, 13));
            Assert::IsTrue(pkb.isNext(12, 13));
            Assert::IsTrue(pkb.isNext(5, 3));
            Assert::IsTrue(pkb.isNext(17, 15));    // Corner-case 1: Nested if-else in else-block, immediate exit
            Assert::IsTrue(pkb.isNext(20, 15));    // Corner-case 1: Nested if-else in else-block, immediate exit
            Assert::IsTrue(pkb.isNext(21, 15));    // Corner-case 1: Nested if-else in else-block, immediate exit
            Assert::IsTrue(pkb.isNext(24, 30));    // Corner-case 2: Nested while stmt in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(27, 30));    // Corner-case 2: Nested while stmt in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(58, 64));    // Corner-case 3: Nested if-else in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(59, 64));    // Corner-case 3: Nested if-else in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(62, 64));    // Corner-case 3: Nested if-else in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(63, 64));    // Corner-case 3: Nested if-else in if-block and else-block, immediate exit
            Assert::IsTrue(pkb.isNext(13, 8));     // Loop back (while)
            Assert::IsTrue(pkb.isNext(53, 51));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsTrue(pkb.isNext(51, 50));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsTrue(pkb.isNext(50, 54));    // Corner-case 4: Nested while stmt in while stmt, immediately exit

            // Test for false cases
            Assert::IsFalse(pkb.isNext(1, 3));
            Assert::IsFalse(pkb.isNext(5, 6));
            Assert::IsFalse(pkb.isNext(5, 7));
            Assert::IsFalse(pkb.isNext(6, 7));
            Assert::IsFalse(pkb.isNext(10, 13));
            Assert::IsFalse(pkb.isNext(13, 14));
            Assert::IsFalse(pkb.isNext(17, 22));
            Assert::IsFalse(pkb.isNext(20, 22));
            Assert::IsFalse(pkb.isNext(21, 22));
            Assert::IsFalse(pkb.isNext(26, 23));
            Assert::IsFalse(pkb.isNext(29, 23));
            Assert::IsFalse(pkb.isNext(26, 30));    // Corner-case 2: Nested while stmt in if-block and else-block, immediate exit
            Assert::IsFalse(pkb.isNext(29, 30));    // Corner-case 2: Nested while stmt in if-block and else-block, immediate exit
            Assert::IsFalse(pkb.isNext(35, 36));
            Assert::IsFalse(pkb.isNext(40, 41));
            Assert::IsFalse(pkb.isNext(48, 49));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsFalse(pkb.isNext(51, 54));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsFalse(pkb.isNext(53, 50));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsFalse(pkb.isNext(53, 54));    // Corner-case 4: Nested while stmt in while stmt, immediately exit
            Assert::IsFalse(pkb.isNext(55, 64));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsComputation)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsSource1());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffects(1, 3));
            Assert::IsTrue(pkb.isAffects(1, 7));
            Assert::IsTrue(pkb.isAffects(3, 3));
            Assert::IsTrue(pkb.isAffects(3, 5));
            Assert::IsTrue(pkb.isAffects(3, 6));
            Assert::IsTrue(pkb.isAffects(3, 7));
            Assert::IsTrue(pkb.isAffects(5, 3));
            Assert::IsTrue(pkb.isAffects(5, 5));
            Assert::IsTrue(pkb.isAffects(5, 6));
            Assert::IsTrue(pkb.isAffects(5, 7));
            Assert::IsFalse(pkb.isAffects(1, 2));

            Assert::IsTrue(pkb.getAllAffects().first.size() == 10);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsComputation2)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsSource2());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffects(1, 8));
            Assert::IsTrue(pkb.isAffects(3, 5));
            Assert::IsTrue(pkb.isAffects(3, 7));
            Assert::IsFalse(pkb.isAffects(1, 2));

            Assert::IsTrue(pkb.getAllAffects().first.size() == 3);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsComputation3)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsSource3());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffects(2, 5));
            Assert::IsTrue(pkb.isAffects(5, 2));
            Assert::IsTrue(pkb.isAffects(7, 2));
            Assert::IsTrue(pkb.isAffects(7, 5));
            Assert::IsTrue(pkb.isAffects(7, 8));
            Assert::IsTrue(pkb.isAffects(8, 2));
            Assert::IsTrue(pkb.isAffects(8, 5));
            Assert::IsTrue(pkb.isAffects(8, 8));
            Assert::IsFalse(pkb.isAffects(7, 7));

            Assert::IsTrue(pkb.getAllAffects().first.size() == 8);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsComputation4)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsSource4());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffects(1, 4));
            Assert::IsTrue(pkb.isAffects(3, 6));
            Assert::IsTrue(pkb.isAffects(3, 11));
            Assert::IsTrue(pkb.isAffects(3, 12));
            Assert::IsTrue(pkb.isAffects(6, 7));
            Assert::IsTrue(pkb.isAffects(14, 4));
            Assert::IsTrue(pkb.isAffects(14, 11));
            Assert::IsTrue(pkb.isFollows(5, 15));
            Assert::IsTrue(pkb.isAffectsStar(15, 4));

            Assert::IsTrue(pkb.getAllAffects().first.size() == 14);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsStarComputation)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsStarSource());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffectsStar(1, 3));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsStarComputation2)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsStarSource2());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsTrue(pkb.isAffectsStar(9, 21));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestAffectsStarComputation3)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_affectsStarSource3());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));


            // Test for affects
            Assert::IsFalse(pkb.isAffectsStar(1, 16));
            Assert::IsTrue(pkb.isAffectsStar(11, 19));
            Assert::IsTrue(pkb.isAffectsStar(16, 16));
            Assert::IsTrue(pkb.isAffectsStar(19, 19));
            Assert::IsTrue(pkb.isAffectsStar(3, 19));
            Assert::IsTrue(pkb.isAffectsStar(7, 19));
            Assert::IsFalse(pkb.isAffectsStar(9, 19));
            Assert::IsFalse(pkb.isAffectsStar(1, 16));
            Assert::IsFalse(pkb.isAffectsStar(6, 16));
            Assert::IsFalse(pkb.isAffectsStar(9, 16));
            Assert::IsTrue(pkb.isAffectsStar(1, 13));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testAddStmtList)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_iteration3complexity());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Test for correct adding of stmtList in PKB
            actualResults = pkb.getStmtList();
            expectedResults = list<int>{
                1, 7, 8, 10, 13, 17, 19, 31, 33, 36, 38, 40,
                42, 45, 49, 52,54, 57, 62, 65, 69, 72 };
            actualResults.sort();
            expectedResults.sort();

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());

        }

        TEST_METHOD(testParsingSimpleSource_prototypeStandard_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_prototypeStandard());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsOnly_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsCalls_success)
        {
            // Set up
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsAndCalls());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(manyCalls_success)
        {
            // Set up
            list<string> actualStringResults;
            list<string> expectedStringResults;
            list<int> actualIntResults;
            list<int> expectedIntResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest2());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Check if all procedures added correctly
            actualIntResults = pkb.getAllProcedures();
            expectedIntResults = list<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
            Assert::IsTrue(actualIntResults.size() == expectedIntResults.size());
            actualIntResults.sort();
            expectedIntResults.sort();
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_iteration3complexity)
        {
            // Set up
            list<string> actualStringResults;
            list<string> expectedStringResults;
            list<int> actualIntResults;
            list<int> expectedIntResults;
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_iteration3complexity());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Check if all assignment statements are added correctly
            actualIntResults = pkb.getAllAssignments();
            expectedIntResults = list<int>{
                1, 2, 3, 4, 5, 8, 10, 11, 12, 14, 15, 17, 19, 20, 21, 22, 23,
                24, 26, 27, 28, 29, 31, 33, 34, 35, 36, 38, 39, 40, 42, 43, 45,
                46, 47, 49, 50, 52, 53, 54, 55, 56, 57, 58, 59, 61, 62, 63, 65,
                66, 69, 70, 71, 72, 73, 74, 75
            };
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Check if all if-else statements are added correctly
            actualIntResults = pkb.getAllIfs();
            expectedIntResults = list<int>{ 9, 30, 48, 51 };
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Check if all while statements are added correctly
            actualIntResults = pkb.getAllWhiles();
            expectedIntResults = list<int>{ 6, 7, 16, 18, 32, 37, 41, 44, 64, 68 };
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Check if all call statements are added correctly
            actualIntResults = pkb.getAllCallsStmt();
            expectedIntResults = list<int>{ 13, 25, 60, 67 };
            Assert::IsTrue(actualIntResults == expectedIntResults);

            // Check if all parents are deduced correctly
            actualIntResults = pkb.getAllParents(Entity::STMT);   // Any statements
            expectedIntResults = list<int>{ 6, 7, 9, 16, 18, 30, 32, 37, 41, 44, 48, 51, 64, 68 };

            // Jump. Add more incremental test here.

            // Check if inter-procedural Uses and Modifies are set correctly.
            int targetProcIdx = (pkb.convertStringToIdx(list<string>{"GHI"}, Entity::PROCEDURE)).front();
            actualIntResults = pkb.getUsesFromProc(targetProcIdx);
            actualStringResults = pkb.convertIdxToString(actualIntResults, Entity::VARIABLE);
            expectedStringResults = list<string>{ "funnyVar", "laugh", "w", "a", "b", "tmp", "oSCar", "Romeo", "best", "supper" };
            actualStringResults.sort();
            expectedStringResults.sort();
            Assert::IsTrue(actualStringResults == expectedStringResults);

            targetProcIdx = (pkb.convertStringToIdx(list<string>{"GHI"}, Entity::PROCEDURE)).front();
            actualIntResults = pkb.getModifiesFromProc(targetProcIdx);
            actualStringResults = pkb.convertIdxToString(actualIntResults, Entity::VARIABLE);
            expectedStringResults = list<string>{ "funnyVar", "laugh", "a", "w", "b", "oSCar", "food", "best", "supper" };
            actualStringResults.sort();
            expectedStringResults.sort();
            Assert::IsTrue(actualStringResults == expectedStringResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*******************************
         * Utility Methods for Testing *
         *******************************/
        TEST_METHOD(testDummySimpleSourceFileUtilityMethods)
        {
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_nonNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_assignments_2LevelNestedWhile());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only.
        */
        bool createDummySimpleSourceFile_assignmentsOnly() {
            std::string content = "procedure ABC{\n  a = 1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with syntax error.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_missingEqual() {
            std::string content = "procedure ABC{\n  a  1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with missing semicolon.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_missingSemicolon() {
            std::string content = "procedure ABC{\n  a = 1;\n b = 2;\n	c = a\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only, with wrong procedure name.
        */
        bool createDummySimpleSourceFile_assignmentsOnly_wrongProcName() {
            std::string content = "procedure 3abc {\n  a  1;\n b = 2;\n	c = a;\n }\n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and a while loop without nesting.
        */
        bool createDummySimpleSourceFile_whileOnly() {
            std::string content = "procedure ABC { \ni = j; \nj = 3 + 5; \nwhile a \n{ \n	a = 3; \n   b = 2  ; \nc = 4; \nd = 5; \n} \nc = c + d; \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and a while loop without nesting.
        */
        bool createDummySimpleSourceFile_assignments_nonNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n	a = 3; \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n		a = b; \n		c = 3; \n		d = 4; \n        while tmp{ \n		d = c + a; \n		e = d + 3 + 4 * 5; \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n	c = 3 + a * e + d; \n        x = x + 1;} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile2() {
            std::string content = "procedure One { \n	a = a + b + c + c + b + a; \n \n	while c { \n		c = a + b; \n	} \n \n	while c { \n		while b { \n			a = a + b + c + c + b + a; \n			b = b + b; \n		} \n	} \n}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 1-level nested while loops.
        Missing boolean variable in while statement header.
        */
        bool createDummySimpleSourceFile_assignments_1LevelNestedWhile_missingBoolVar() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile  \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n		a = b; \n		c = 3; \n		d = 4; \n        while tmp{ \n		d = c + a; \n		e = d + 3 + 4 * 5; \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n	c = 3 + a * e + d; \n        x = x + 1;} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 2-level nested while loops.
        */
        bool createDummySimpleSourceFile_assignments_2LevelNestedWhile() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n        while tmp{ \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n        x = x + 1; \n        while left { \n            x = x+ 1	; }} \n          a=   2; } \n   w = w+1  ; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and if-else statements without nesting.
        */
        bool createDummySimpleSourceFile_simpleNextRelation1() {
            std::string content =
                "procedure ABC { \n"
                "	a = 1; \n"
                "	b = 2; \n"
                "	while x { \n"
                "		c = 4; \n"
                "		if x then { \n"
                "			i = 6; \n"
                "		} else { \n"
                "			j = 7; \n"
                "		} \n"
                "		k = 8; \n"
                "	} \n"
                "	l = 9; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and if-else statements without nesting.
        */
        bool createDummySimpleSourceFile_comprehensiveNextRelations() {
            std::string content =
                "procedure ABC { \n"
                "	a = 1; \n"
                "	b = 2; \n"
                "	while x { \n"
                "		if x then { \n"
                "			i = 5; \n"
                "		} else { \n"
                "			j = 6; \n"
                "		} \n"
                "	} \n"
                "	k = 7; \n"
                "	while a { \n"
                "		a = 9; \n"
                "		if x then { \n"
                "			b = 11; \n"
                "		} else { \n"
                "			c = 12; \n"
                "		} \n"
                "		d = 13; \n"
                "	} \n"
                "	f = 14; \n"
                "	while b { \n"
                "		if x then { \n"
                "			b = 17; \n"
                "		} else { \n"
                "			c = 18; \n"
                "			if a then { \n"
                "				c = 20; \n"
                "			} else { \n"
                "				d = 21; \n"
                "			} \n"
                "		} \n"
                "	} \n"
                "	f = 22; \n"
                "	if a then { \n"
                "		while x { \n"
                "			a = 25; \n"
                "			b = 26; \n"
                "		} \n"
                "	} else { \n"
                "		while x { \n"
                "			a = 28; \n"
                "			b = 29; \n"
                "		} \n"
                "	} \n"
                "	f = 30; \n"
                "	if a then { \n"
                "		d = 32; \n"
                "		while x { \n"
                "			a = 34; \n"
                "			b = 35; \n"
                "		} \n"
                "		d = 36; \n"
                "	} else { \n"
                "		c = 37; \n"
                "		while x { \n"
                "			a = 39; \n"
                "			b = 40; \n"
                "		} \n"
                "		c = 41; \n"
                "	} \n"
                "	f = 42; \n"
                " while a { \n"
                "		b = 44; \n"
                "		while b { \n"
                "			c = 46; \n"
                "			c = c + 1; \n"
                "		} \n"
                "		a = 48; \n"
                "	} \n"
                "	f = 49; \n"
                " while a { \n"
                "		while b { \n"
                "			c = 46; \n"
                "			c = c + 1; \n"
                "		} \n"
                "	} \n"
                " f = 54; \n"
                " if x then { \n"
                "		if b then { \n"
                "			a = 3; \n"
                "			d = 4; \n"
                "		} else { \n"
                "			a = 5; \n"
                "		} \n"
                "	} else { \n"
                "		if b then { \n"
                "			a = 3; \n"
                "			d = 4; \n"
                "		} else { \n"
                "			f = 5; \n"
                "		} \n"
                "	} \n"
                " f = 54; \n"
                " if x then { \n"
                "		a = 64; \n"
                "		if b then { \n"
                "			a = 3; \n"
                "			d = 4; \n"
                "		} else { \n"
                "			f = a + d; \n"
                "		} \n"
                "		d = 68; \n"
                "	} else { \n"
                "		f = 69; \n"
                "		if b then { \n"
                "			a = 3; \n"
                "			d = 4; \n"
                "		} else { \n"
                "			f = 19; \n"
                "		} \n"
                "		f = 73; \n"
                "	} \n"
                "	f = 68; \n"
                "} ";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements and 2-level nested while loops.
        The dummy SIMPLE program is up to the standard of iteration1.0 testing.
        */
        bool createDummySimpleSourceFile_prototypeStandard() {
            std::string content = "procedure ABC { \n  i=1; \n b=200 ; \n	c= a   ; \nwhile a \n{ \n   while beta { \n        oSCar  = 1 + beta + tmp; \n        while tmp{ \n          oSCar = I + k + j1k + chArlie; } \n	while x { \n        x = x + 1; \n        while left { \n          while right { \n            Romeo = Romeo + 1; \n			f = 3; \n            b = 0; \n            c = delta    + l  + width + Romeo ; } \n            while c { \n			b = d + 1; \n			g = 3 + 2; \n              c = c +1   	; } \n			c = b - 5; \n			b = c - a; \n            x = x+ 1	; }} \n		e = g - 1; \n          a=   2; } \n   w = w+1  ; \n   w = 2		; \n   i = w; \n} \n} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source with
        multiple procedures, all containing assignment statements only.
        */
        bool createDummySimpleSourceFile_multiProcs_assignmentsOnly() {
            std::string content = "procedure ABC{ \n  a = 1; \n b = 2; \n	c = a; \n } \n \nprocedure DEF{ \n  a = 1; \n b = 2; \n	c = a; \n } \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source with
        multiple procedures, all containing assignment statements and
        valid call statements only.
        */
        bool createDummySimpleSourceFile_multiProcs_assignmentsAndCalls() {
            std::string content = "procedure ABC{ \n  a = 1; \n b = 2; \n call DEF; \n	c = a; \n } \n \nprocedure DEF{ \n  a = 1; \n b = 2; \n	c = a; \n } \n ";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source
        containing assignment statements and non-nested if-else
        statements.
        */
        bool createDummySimpleSourceFile_assignments_nonNestedIfElse() {
            std::string content =
                "procedure ABC { \n"
                "	i=1; \n"
                "	b=200 ; \n"
                "	c= a   ; \n"
                "	if a then \n"
                "	{ \n"
                "		a = 3; \n"
                "		w = w+1  ; \n"
                "	} else { \n"
                "		a = c + b; \n"
                "		w = a; \n"
                "	} \n"
                "	d = c + 200 * 400 - i; \n"
                "	 \n"
                "	if b then { \n"
                "		a = c * 30 * 400; \n"
                "		w = a - a; \n"
                "	} \n"
                "	else \n"
                "	{ \n"
                "		d = 100; \n"
                "	} \n"
                "	 \n"
                "	d = d + 1; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source
        containing assignment statements and non-nested if-else
        statements.
        */
        bool createDummySimpleSourceFile_SimpleTest2() {
            std::string content =
                "procedure One { \n"
                "	while a { \n"
                "		call Two; } \n"
                "	call Three; } \n"
                "	 \n"
                "procedure Three { \n"
                "	b = c + d; \n"
                "	if e then { \n"
                "		call Four; } \n"
                "	else { \n"
                "		call Five; } \n"
                "	call Six; } \n"
                "	 \n"
                "procedure Four { \n"
                "	while f { \n"
                "		g = 2 * h + (3 * 5) - 14 + 100 * a; } } \n"
                " \n"
                "procedure Five { \n"
                "	while i { \n"
                "		j = 10 + (3 * 5) + 100 * a - 2 * h; \n"
                "		if j then { \n"
                "			call Six; } \n"
                "		else { \n"
                "			call Seven; } \n"
                "		k = j + g * (100 * a); } } \n"
                "		 \n"
                "procedure Six { \n"
                "	l = 22 + m - 3 * 9 + a; \n"
                "	if m then { \n"
                "		call Seven; } \n"
                "	else { \n"
                "		while n { \n"
                "			m = 2 * h; } } \n"
                "	p = 2 * h; } \n"
                "	 \n"
                "procedure Two { \n"
                "	o = o + i - 100 + a * 2; \n"
                "	call Eight; \n"
                "	q = 10 - r; } \n"
                "	 \n"
                "procedure Seven { \n"
                "	while s { \n"
                "		s = q + 2 - t; } \n"
                "	call Nine; \n"
                "	while u { \n"
                "		if q then { \n"
                "			t = s; } \n"
                "		else { \n"
                "			u = 10 + 2 - t; } } } \n"
                "			 \n"
                "procedure Eight { \n"
                "	call Nine; \n"
                "	v = w + 3 - 2 * h; } \n"
                " \n"
                "procedure Nine { \n"
                "	x = y; \n"
                "	y = x; \n"
                "	z = x; \n"
                "	z = q; }";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source
        complex enough for iteration3.0.
        */
        bool createDummySimpleSourceFile_iteration3complexity() {
            std::string content =
                "procedure ABC { \n"
                "  i=1; \n"
                " b=200 ; \n"
                " Romeo = c + a * (b - i * a) - 5 * 3 + 1; \n"
                " b = c * (b - a) * ((3 * Romeo) - (2 * (3 - 1))); \n"
                "	c= a   ; \n"
                "while a \n"
                "{ \n"
                "   while beta { \n"
                "        oSCar  = 1 + beta + tmp; \n"
                "		if a then { \n"
                "			oSCar = oSCar - beta; \n"
                "			c = b; \n"
                "			b = a; \n"
                "		} else { \n"
                "			call GHI; \n"
                "			Romeo = beta + c* b; \n"
                "			d = b - 3; \n"
                "		} \n"
                "		 \n"
                "	while x { \n"
                "        x = x + 1; \n"
                "        while left { \n"
                "			c = b - 5; \n"
                "			b = c - a; \n"
                "            x = x+ 1	; }} \n"
                "		e = g - 1; \n"
                "          a=   2; } \n"
                "   w = w+1  ; \n"
                "   call DEF; \n"
                "   w = 2		; \n"
                "   i = w; \n"
                "} \n"
                "b = c + a; \n"
                "	beta = 100; \n"
                "	if beta then { \n"
                "		beta = beta * 2; \n"
                "		while beta { \n"
                "			beta = beta - 1; \n"
                "			b = b + c + a; \n"
                "			c = c + a; \n"
                "		}	} else {		beta = 50; \n"
                "		while beta { \n"
                "			beta = beta - 1; \n"
                "			c = c + a; \n"
                "		} \n"
                "	} \n"
                "} \n"
                " \n"
                "procedure GHI	 { \n"
                "	funnyVar = 101; \n"
                "	while funnyVar { \n"
                "		laugh = 10; \n"
                "		funnyVar = funnyVar - 1; \n"
                "		while laugh { \n"
                "			laugh = laugh - 1; \n"
                "		} \n"
                "	} \n"
                "	w = 3 + a; \n"
                "	a = 10; \n"
                "	if w then { \n"
                "		w = a; \n"
                "		laugh = w; \n"
                "		if b then { \n"
                "			b = b * 3 - tmp + oSCar; \n"
                "			oSCar = Romeo; \n"
                "		} else { \n"
                "			w = 1000; \n"
                "			a = 2; \n"
                "		} \n"
                "		w = a; \n"
                "	} else { \n"
                "		a = 2; \n"
                "		w = laugh; \n"
                "	} \n"
                "	funnyVar = 0; \n"
                "	call NotSharingVar; \n"
                "	funnyVar = 10; \n"
                "} \n"
                " \n"
                "procedure DEF { \n"
                "	a = 123; \n"
                "	b = 345; \n"
                "	while a { \n"
                "		c = b; \n"
                "		b = 482; \n"
                "		call GHI; \n"
                "		while b { \n"
                "			laugh = laugh + 1; \n"
                "		} \n"
                "	} \n"
                "	c = b + a; \n"
                "	b = 1000; \n"
                "} \n"
                " \n"
                "procedure NotSharingVar { \n"
                "	best = 1; \n"
                "	food = best; \n"
                "	supper = best * best; \n"
                "	supper = supper * best; \n"
                "} \n";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source to test
        PKB's Affects computation.
        */
        bool createDummySimpleSourceFile_affectsSource1() {
            std::string content =
                "procedure Test { \n"
                "	a = b; \n"
                "	while b { \n"
                "		a = c + a; \n"
                "		while c { \n"
                "			a = d + a; \n"
                "		} \n"
                "		b = a; \n"
                "	} \n"
                "	d = a; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy SIMPLE source to test
        PKB's Affects computation.
        */
        bool createDummySimpleSourceFile_affectsSource2() {
            std::string content =
                "procedure Test { \n"
                "	a = b; \n"
                "	if x then { \n"
                "		a = c; \n"
                "		if y then { \n"
                "			y = a; \n"
                "           a = b; \n"
                "		} else { \n"
                "		    q = b + a; \n"
                "	    } \n"
                "	} else { \n"
                "       x = a + b; \n"
                "   } \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsSource3() {
            std::string content =
                "procedure Test { \n"
                "	while battle1{ \n"
                "		charmeleon = wartortle + ivysaur; \n"
                "		while battle2{ \n"
                "			while battle3{ \n"
                "				ivysaur = charmeleon + wartortle; \n"
                "			} \n "
                "			if wartortle then{ \n"
                "				wartortle = squirtle + 3; \n"
                "			} \n"
                "			else { \n"
                "				wartortle = wartortle - 1; \n"
                "			} \n"
                "		} \n"
                "		lastPokemon = 3; \n"
                "	} \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsSource4() {
            std::string content =
                "procedure Test { \n"
                "	a = 5; \n"
                "	while x { \n"
                "		b = c + b; \n"
                "		t = t + a; \n"
                "		if b then { \n"
                "			n = b + m; \n"
                "			b = n * 2 + k; \n"
                "			n = b - b; \n"
                "			call Bob; \n" //modifies b & n
                "			m = n + k - n + n; }\n"
                "		else { \n"
                "			a = a + b; \n"
                "			b = b; \n"
                "			call John; \n" //modifies b
                "			a = b * m * n; } \n"
                "		m = b; \n"
                "		n = 2; } \n"
                "	call Bob; \n" //modifies b & n
                "} \n"
                "procedure Bob { \n "
                "	b = 3; \n"
                "	n = b; \n"
                "} \n"
                "procedure John { \n"
                "	b = 3; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsSource5() {
            std::string content =
                "procedure IfWhile { \n"
                "	if dream then { \n"
                "		sleep = 100 + 5; \n"
                "		while sleep { \n"
                "			inBattle = 100 - 5 - sleep; \n"
                "			knowledge = 5 - 20; }\n"
                "	} else { \n "
                "		sleep = knowledge + dream; }\n"
                "	while sleep { \n"
                "		sleep = sleep + 2; }\n"
                "	dream = sleep * 5000; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsStarSource() {
            std::string content =
                "procedure IfWhile { \n"
                "	a = 2; \n"
                "	b = a; \n"
                "	c = b; \n"
                "}";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsStarSource2() {
            std::string content = "procedure WhileMultiple { sarada = sakura + sasuke; shikamaru = shikamaru + 100 ; while naruto { naruto = 2 + kurama ; sakura = love - 5; while sasuke { sakura = love + 100 ; sakura = naruto - 100 ; attack = 10 + 100; while kakashi { shadowClone = naruto + kakashi; while sageMode { while inBattle { jiraya = attack + 100 * knowledge - 5;} naruto = attack +100; } while inBattle { kakashi = naruto + jiraya; attack = attack * 5; } } sarada = love * 100; } inBattle= sageMode * love* knowledge; } knowledge =sleep + inBattle + love + naruto; } procedure IfMultiple { boruto = naruto + hinata; if inBattle then { boruto = attack + 5; boruto = shadowClone + 5; if naruto then { boruto = love - 20 ; boruto = boruto*shadowClone - 20 ; hinata = love + 100; if hinata then { himawari = love + 100; if inBattle then { hinata= attack +100* naruto * love+ 100 - boruto ; himawari=hinata*naruto+love; } else { knowledge =naruto + hinata * himawari - boruto ; } } else { knowledge = love * 0; } if sakura then { knowledge = hinata * love -sakura * love; } else { shadowClone = shadowClone+ 3; } naruto = sleep; } else { boruto = knowledge + 2; love = sarada + boruto; } } else { kakashi = inBattle; if inBattle then { kakashi = sageMode - 5 + boruto - 5; shadowClone = 100 * shadowClone ; } else { kakashi = sleep + 5; shadowClone = shadowClone - 10; knowledge = sleep + 10; } kakashi = shadowClone * 0; if love then { kakashi = love + 5 ; love = knowledge + shadowClone + sageMode; } else { naruto = inBattle ; boruto = inBattle; } } } procedure WhileIf { inBattle = naruto + sasuke ; while inBattle { if naruto then { naruto = shadowClone* sageMode *attack+ 100; } else { sasuke = knowledge* 100 - naruto; } } if sleep then { dream =naruto + hinata + boruto + himawari; } else { boruto = hinata + himawari - naruto; } } procedure IfWhile { if dream then { sleep = 100 + 5; while sleep { inBattle = 100 - 5 -sleep; knowledge = 5 - 20; } } else { sleep = knowledge + dream; } while sleep { sleep = sleep + 2; } dream = sleep * 5000; } ";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        bool createDummySimpleSourceFile_affectsStarSource3() {
            std::string content = "procedure pokemon { charmander = 5; squirtle = 5; bulbasaur = 5; firstStageEvolution = 11; while firstStageEvolution { charmander = charmander + 1; bulbasaur = bulbasaur + 1; squirtle = squirtle + 1; } charmeleon = charmander; wartortle = squirtle; ivysaur = bulbasaur; battle1 = charmeleon - wartortle; battle2 = ivysaur - charmeleon; battle3 = squirtle - ivysaur; while battle1 { charmeleon = wartortle + ivysaur; while battle2 { while battle3 { ivysaur = charmeleon + wartortle; } if wartortle then { wartortle = squirtle + 3; } else { wartortle = wartortle - 1; } } lastPokemon = 3; } }";
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        // This is a utility method to destroy the dummy text file created by createDummyTextFile()
        bool deleteDummySimpleSourceFile() {
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            return std::remove(newFilePath.c_str()) == 0;
        }
    };
}
