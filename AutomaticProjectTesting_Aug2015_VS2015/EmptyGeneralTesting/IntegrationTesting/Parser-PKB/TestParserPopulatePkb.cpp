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
        PKBMain dummyPkbMain;
        PKBMain* dummyPkbMainPtr = &dummyPkbMain;

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_equalSignMissing)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingEqual());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_missingSemicolon)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_missingSemicolon());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentsOnly_wrongProcName)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignmentsOnly_wrongProcName());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_whileOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_whileOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_nonNextedIfElse_success)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_nonNestedIfElse());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Test adding of if-else statements
            actualResults = dummyPkbMain.getAllIfs();
            expectedResults = list<int>{ 4, 10 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Test if parents are updated correctly
            actualResults = dummyPkbMain.getAllParents(Entity::STMT);
            expectedResults = list<int>{ 4, 10 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            actualResults = dummyPkbMain.getAllParents(Entity::IF);
            expectedResults = list<int>{ 4, 10 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Test if children are updated correctly
            actualResults = dummyPkbMain.getAllChildren(Entity::STMT);
            expectedResults = list<int>{ 5, 6, 7, 8, 11, 12, 13 };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile2_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile2());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd1LevelNestedWhile_missingBoolVar)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_1LevelNestedWhile_missingBoolVar());

            Assert::IsFalse(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_assignmentAnd2LevelNestedWhile_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_assignments_2LevelNestedWhile());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_prototypeStandard_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_prototypeStandard());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsOnly_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsOnly());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_multiProcAssignmentsCalls_success)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_multiProcs_assignmentsAndCalls());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(testParsingSimpleSource_iteration3complexity)
        {
            // Set up
            list<int> actualResults;
            list<int> expectedResults;
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_iteration3complexity());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            // Check if all assignment statements are added correctly
            actualResults = dummyPkbMain.getAllAssignments();
            expectedResults = list<int>{ 
                1, 2, 3, 4, 5, 8, 10, 11, 12, 14, 15, 17, 19, 20, 21, 22, 23,
                24, 26, 27, 28, 29, 31, 33, 34, 35, 36, 38, 39, 40, 42, 43, 45,
                46, 47, 49, 50, 52, 53, 54, 55, 56, 57, 58, 59, 61, 62, 63, 65,
                66, 69, 70, 71, 72, 73, 74, 75
            };
            Assert::IsTrue(actualResults == expectedResults);

            // Check if all if-else statements are added correctly
            actualResults = dummyPkbMain.getAllIfs();
            expectedResults = list<int>{ 9, 30, 48, 51 };
            Assert::IsTrue(actualResults == expectedResults);

            // Check if all while statements are added correctly
            actualResults = dummyPkbMain.getAllWhiles();
            expectedResults = list<int>{ 6, 7, 16, 18, 32, 37, 41, 44, 64, 68 };
            Assert::IsTrue(actualResults == expectedResults);

            // Check if all call statements are added correctly
            actualResults = dummyPkbMain.getAllCallsStmt();
            expectedResults = list<int>{ 13, 25, 60, 67 };
            Assert::IsTrue(actualResults == expectedResults);

            // Check if all parents are deduced correctly
            actualResults = dummyPkbMain.getAllParents(Entity::STMT);   // Any statements
            expectedResults = list<int>{ 6, 7, 9, 16, 18, 30, 32, 37, 41, 44, 48, 51, 64, 68 };

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

        // This is a utility method to destroy the dummy text file created by createDummyTextFile()
        bool deleteDummySimpleSourceFile() {
            std::string newFilePath("../UnitTesting/ParserTestDependencies/dummySimpleSource.txt");
            return std::remove(newFilePath.c_str()) == 0;
        }
    };
}
