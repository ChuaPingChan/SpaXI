#include <string>
#include <cstdio>
#include <regex>

#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"
#include "../SPA/PKB/PKBMain.h"
#include "../SPA/PQL/PQLMain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(SystemTest)
    {
        /*
        This class is to emulate simple system tests.
        */
    public:

        const std::string dummySimpleSourcePath = "../IntegrationTesting/ParserTestDependencies/dummySimpleSource.txt";

        TEST_METHOD(bug1Test)
        {
            /*
            Bug description:
            Throws unknown exception when running system test on AutoTester.
            */
            // Set up
            PKBMain* pkbPtr = PKBMain::getInstance();
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "variable v; while w; assign a; prog_line n;\nSelect n such that Modifies(w, _) such that Uses(a, _)";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "1", "2", "3", "4", "5", "6", "7" };
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            pkbPtr->resetInstance();
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(bug2Test)
        {
            // Set up
            PKBMain* pkbPtr = PKBMain::getInstance();
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest2());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "assign a; Select a pattern a(_, \"x\")";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "36", "37" };
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            pkbPtr->resetInstance();
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*******************************
         * Utility Methods for Testing *
         *******************************/
        TEST_METHOD(testDummySimpleSourceFileUtilityMethods)
        {
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest2());
            Assert::IsTrue(deleteDummySimpleSourceFile());
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        // This is a utility method to destroy the dummy text file created by createDummyTextFile()
        bool deleteDummySimpleSourceFile() {
            std::string newFilePath(dummySimpleSourcePath);
            return std::remove(newFilePath.c_str()) == 0;
        }

        /*
        This is a utility method to create a source file for test 2.
        */
        bool createDummySimpleSourceFile_SimpleTest2() {
            std::string content =
                "procedure One { "
                "	while a { "
                "		call Two; } "
                "	call Three; } "
                "	 "
                "procedure Three { "
                "	b = c + d; "
                "	if e then { "
                "		call Four; } "
                "	else { "
                "		call Five; } "
                "	call Six; } "
                "	 "
                "procedure Four { "
                "	while f { "
                "		g = 2 * h + (3 * 5) - 14 + 100 * a; } } "
                " "
                "procedure Five { "
                "	while i { "
                "		j = 10 + (3 * 5) + 100 * a - 2 * h; "
                "		if j then { "
                "			call Six; } "
                "		else { "
                "			call Seven; } "
                "		k = j + g * (100 * a); } } "
                "		 "
                "procedure Six { "
                "	l = 22 + m - 3 * 9 + a; "
                "	if m then { "
                "		call Seven; } "
                "	else { "
                "		while n { "
                "			m = 2 * h; } } "
                "	p = 2 * h; } "
                "	 "
                "procedure Two { "
                "	o = o + i - 100 + a * 2; "
                "	call Eight; "
                "	q = 10 - r; } "
                "	 "
                "procedure Seven { "
                "	while s { "
                "		s = q + 2 - t; } "
                "	call Nine; "
                "	while u { "
                "		if q then { "
                "			t = s; } "
                "		else { "
                "			u = 10 + 2 - t; } } } "
                "			 "
                "procedure Eight { "
                "	call Nine; "
                "	v = w + 3 - 2 * h; } "
                " "
                "procedure Nine { "
                "	x = y; "
                "	y = x; "
                "	z = x; "
                "	z = q; }";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a source file for test 3.
        */
        bool createDummySimpleSourceFile_SimpleTest3() {
            std::string content =
                "procedure One { \n"
                "	a = a + b + c + c + b + a; \n"
                " \n"
                "	while c { \n"
                "		c = a + b; \n"
                "	} \n"
                " \n"
                "	while c { \n"
                "		while b { \n"
                "			a = a + b + c + c + b + a; \n"
                "			b = b + b; \n"
                "		} \n"
                "	} \n"
                "}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }
    };
}
