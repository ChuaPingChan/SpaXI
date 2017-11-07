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
            pkbPtr->deleteInstance();
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
            pkbPtr->deleteInstance();
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(bug3Test)
        {
            // Set up
            PKBMain* pkbPtr = PKBMain::getInstance();
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_Test13());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "constant co; variable v; if i; call c1,c2;procedure p1,p2; "
                "Select i pattern i(v, _, _) such that Modifies(i, v) and Next*(c1, i) with c2.stmt#  = co.value such that Calls(p1, p2)";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "4", "33", "34" };
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            pkbPtr->deleteInstance();
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

        /*
        This is a utility method to create a source file for Test 13.
        */
        bool createDummySimpleSourceFile_Test13() {
            std::string content =
                "procedure p{ a = x + y * b; \n"
                "	c = m - y + z * 3; \n"
                "	call a; \n"
                "	if b then { \n"
                "		while m { \n"
                "			m = m - 1; \n"
                "			k = m + b + d; } \n"
                "		b = b - m; \n"
                "	} else { x = b - d + x; \n"
                "		call q; \n"
                "		y = x + 5 * b; } } \n"
                "procedure q{ if i then { \n"
                "		b = x + (y - m) * i; \n"
                "		x = 2 - 8; \n"
                "		while b { \n"
                "			y = b - c - 3; \n"
                "			x = x + y; \n"
                "			if z then { \n"
                "				a = b * 3 + x + y; \n"
                "				x = i - y * 5; \n"
                "				while z { \n"
                "					a = b; \n"
                "					b = c + 3; \n"
                "					c = b - e; \n"
                "					e = c + d; \n"
                "					while x { \n"
                "						x = x + b; \n"
                "						b = b - 1; }} \n"
                "				if m then { \n"
                "					e = m - 1; \n"
                "					a = x - i; \n"
                "				} else { k = b + k - m; } \n"
                "			} else { if x then { \n"
                "					if m then { \n"
                "						y = x - 5; \n"
                "						call a; \n"
                "						m = y - 1; \n"
                "					} else { b = x + y - m; } \n"
                "					b = x + y + k; \n"
                "				} else { i = m - i; \n"
                "					while i { \n"
                "						y = x; \n"
                "						k = k + 1; \n"
                "						y = z - k - i; }}} \n"
                "			y = m + 3 * (5 * x) * b; } \n"
                "		y = x * x - 3; \n"
                "	} else { y = k - 5; \n"
                "		while k { \n"
                "			x = y; \n"
                "			call a; }}} \n"
                "procedure a{ while b { \n"
                "		while d { \n"
                "			x = m + i; \n"
                "			k = x - z - y; }} \n"
                "	b = m * i - k; \n"
                "	call d; \n"
                "	if i then { \n"
                "		a = b - m - x; \n"
                "	} else { e = b - m; \n"
                "		c = e + b * x; } \n"
                "	a = e + k; } \n"
                "procedure d { y = i + m + b; \n"
                "	if y then { \n"
                "		if m then { \n"
                "			if k then { \n"
                "				k = k + 1; \n"
                "			} else { y = y - 1; } \n"
                "		} else { y = y + 1; } \n"
                "	} else { while y { \n"
                "			y = y + k; \n"
                "			if y then { \n"
                "				k = k - m; \n"
                "			} else { c = b - m - x; }}} \n"
                "	c = k + y * 3;}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a source file for Test 13.
        */
        bool createDummySimpleSourceFile_Test18() {
            std::string content =
                "procedure A { \n"
                "	and = and + 2 * variable + ((Modifies * Uses - assign) + 5 + 7 * pattern - with) + such * that; \n"
                "	while and { \n"
                "		Uses = Modifies + tab13 * 5 - 9 + 5 + 7; \n"
                "	} \n"
                "	call stmt; \n"
                "	if pattern then { \n"
                "		such = with * and + (and + 2 * variable) - 5 + 7; \n"
                "	} \n"
                "	else { \n"
                "		tab13 = pattern + 8 * 5 + (Modifies - Uses + (assign - with + and) * variable) - tab13 + (assign - 4 * 8 + 3) - (5 * 7) + pattern; \n"
                "	} \n"
                "	call Modifies; \n"
                "} \n"
                " \n"
                "procedure stmt { \n"
                "	pattern = with + and - such + that + (5 * 7); \n"
                "	call Key; \n"
                "	Uses = with * pattern; \n"
                "} \n"
                " \n"
                "procedure Modifies { \n"
                "	Modifies = Uses * 3 + 4 - 1000 - 5 + and; \n"
                "	tab13 = Modifies - Uses * and; \n"
                "	call Chair; \n"
                "	tab13 = Modifies - pattern + with * such; \n"
                "	while Modifies { \n"
                "		Uses = Modifies; \n"
                "	} \n"
                "} \n"
                " \n"
                "procedure Key { \n"
                "	variable = tab13 + 3 * Modifies - and; \n"
                "	and = variable + tab13; \n"
                "	call Wire; \n"
                "	call Cave; \n"
                "} \n"
                " \n"
                "procedure Wire { \n"
                "	call Sugar; \n"
                "	call Sugar; \n"
                "} \n"
                " \n"
                "procedure Sugar { \n"
                "	and = Modifies - Uses * 7; \n"
                "	call Salt; \n"
                "	Modifies = Uses + 9; \n"
                "} \n"
                " \n"
                "procedure Salt { \n"
                "	Uses = Uses; \n"
                "	call Tab13; \n"
                "	call Tab13; \n"
                "} \n"
                " \n"
                "procedure Tab13 { \n"
                "	such = 0 + and - tab13; \n"
                "	call Chair; \n"
                "} \n"
                " \n"
                "procedure Chair { \n"
                "	call Kite; \n"
                "	while Uses { \n"
                "		and = and; \n"
                "		assign = assignment - and; \n"
                "		assignment = and * with - 50; \n"
                "	} \n"
                "} \n"
                " \n"
                "procedure Kite { \n"
                "	call Wifi; \n"
                "	assign = pattern * such + that - 5; \n"
                "	if assign then { \n"
                "		Modifies = with - pattern + 3 * 4; \n"
                "	} \n"
                "	else { \n"
                "		variable = 100 + 3 - 2; \n"
                "	} \n"
                "} \n"
                " \n"
                "procedure Cave { \n"
                "	call Smile; \n"
                "	call Wifi; \n"
                "	pattern = and - with * 4 + 2 - 100; \n"
                "} \n"
                " \n"
                "procedure Smile { \n"
                "	call Pencil; \n"
                "	Modifies = Uses + 1; \n"
                "	Uses = pattern * 100 - 2 * 5 + pattern - assign; \n"
                "	assign = assign + assign + assign; \n"
                "} \n"
                " \n"
                "procedure Pencil { \n"
                "	variable = variable + variable * 2; \n"
                "	call Kite; \n"
                "} \n"
                " \n"
                "procedure Wifi { \n"
                "	assignment = assignment + pattern + assign - and * 100 - 20 + 5 * 2; \n"
                "	and = Uses; \n"
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
