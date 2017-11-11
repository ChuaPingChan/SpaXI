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

        TEST_METHOD(bug4Test)
        {
            // Set up
            PKBMain* pkbPtr = PKBMain::getInstance();
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_Test1());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "stmt s1, s2, s3; Select s1 such that Parent(s1, s2) and Parent(s2, s3)";
            PQLMain pql = PQLMain(query);
            actualResults = pql.run();
            expectedResults = list<string>();
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            query = "stmt s1, s2, s3; Select s2 such that Parent(s1, s2) and Parent(s2, s3)";
            pql = PQLMain(query);
            actualResults = pql.run();
            expectedResults = list<string>();
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            query = "stmt s Select s";
            pql = PQLMain(query);
            actualResults = pql.run();
            expectedResults = list<string>();
            actualResults.sort();
            expectedResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            pkbPtr->deleteInstance();
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(bug5Test)
        {
            // Set up
            PKBMain* pkbPtr = PKBMain::getInstance();
            Parser parser(pkbPtr);
            Assert::IsTrue(createDummySimpleSourceFile_Test13_Source6());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "assign a; variable v; "
                "Select a such that Uses(14, v) pattern a(v, _)";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "2", "8", "11", "19" };
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

        /*
        This is a utility method to create a source file for Test 1.
        */
        bool createDummySimpleSourceFile_Test1() {
            std::string content =
                "procedure ABC { "
                "i = j; "
                "j = 3 + 5; "
                "while a "
                "{ "
                "	a = 3; "
                "   b = 2  ; "
                "c = 4; "
                "d = 5; "
                "} "
                "c = c + d; "
                "}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a source file for Test 13 source6.
        */
        bool createDummySimpleSourceFile_Test13_Source6() {
            std::string content =
                "procedure pokemon { "
                "	charmander = 5; "
                "	squirtle = 5; "
                "	bulbasaur = 5; "
                "	firstStageEvolution = 11; "
                "	while firstStageEvolution { "
                "		charmander = charmander + 1; "
                "		bulbasaur = bulbasaur + 1; "
                "		squirtle = squirtle + 1; "
                "	} "
                "	charmeleon = charmander; "
                "	wartortle = squirtle; "
                "	ivysaur = bulbasaur; "
                "	battle1 = charmeleon - wartortle; "
                "	battle2 = ivysaur - charmeleon; "
                "	battle3 = squirtle - ivysaur; "
                "	while battle1 { "
                "		charmeleon = wartortle + ivysaur; "
                "		while battle2 { "
                "			while battle3 { "
                "				ivysaur = charmeleon + wartortle; "
                "			} "
                "			if wartortle then { "
                "				wartortle = squirtle + 3; "
                "			} "
                "			else { "
                "				wartortle = wartortle - 1; "
                "			} "
                "		} "
                "		lastPokemon = 3; "
                "	} "
                "}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
            This is a utility method to create a source file for Test 16.
        */
        bool createDummySimpleSourceFile_Test16() {
            std::string content =
                "procedure AyamPenyet { "
                "	ayam = 1 + (broccoli + (5 - (9 * (chilli + ayam - 30) + 100 * 2 - date * 20) + (((1 - 5 * 20) - 100 * egg) + fish - ginger + broccoli) - (ayam - honey) * ginger - fish + 100 - 20 * 4) + 20 - 3 * (ginger + broccoli) - fish); "
                "	broccoli = ayam - fish * chilli + egg; "
                "	broccoli = fish + broccoli - egg * ginger; "
                "	egg = date + ayam - fish + iceCream * jam - ketchup; "
                "	date = date - date + date * date; "
                "	mushroom = date + fish - iceCream; "
                "	lime = broccoli + ayam - chilli * egg; "
                "	egg = honey - nutmeg * oats + pea - ayam; "
                "	fish = lime + egg + jam - nutmeg * oats + pea - date * fish + ayam; "
                "	call MeeSiam; "
                "	lime = fish + jam - ayam - broccoli + oats - date; "
                "	chilli = date * fish + lime - broccoli * oats; "
                "	fish = broccoli * oats - jam - date * 10 - 5 + 9 * 20 + oats; "
                "	oats = broccoli * ayam - fish + oats; "
                "	if oats then { "
                "		if broccoli then { "
                "			broccoli = oats + fish - oats * date + broccoli + jam - pea; "
                "			fish = broccoli + oats - ayam + broccoli - ketchup; "
                "			oats = 9 + 100 - 20 + ketchup * 20 - pea + date; "
                "			date = broccoli - ayam + chilli - date; "
                "			broccoli = jam + iceCream - ginger; "
                "			call CarrotCake; "
                "		} "
                "		else { "
                "			call MalaHotpot; "
                "			oats = broccoli + fish - 20; "
                "			ginger = 100 * 2 - date * 20; "
                "			chilli = chilli + ayam - 30; "
                "			fish = fish - ginger + broccoli; "
                "			ayam = ayam - honey; "
                "			broccoli = iceCream + jam; "
                "			oats = ayam + fish + pea - 100; "
                "		} "
                "		honey = fish + jam - ayam - broccoli + oats - date; "
                "		date = date * fish + lime - broccoli * oats; "
                "		jam = broccoli * oats - jam - date * 10 - 5 + 9 * 20 + oats; "
                "		date = broccoli * ayam - fish + oats; "
                "	} "
                "	else { "
                "		fish = (broccoli * oats - jam) - (date * 10) - 5 + (9 * 20) + oats; "
                "		broccoli = honey - nutmeg * oats + pea - ayam; "
                "		call MalaHotpot; "
                "		iceCream = nutmeg * oats; "
                "		honey = fish + iceCream * jam; "
                "	} "
                "	call WantonMee; "
                "	call McSpicy; "
                "	call Rojak; "
                "	oats = chilli + ayam - 3; "
                "} "
                " "
                "procedure MeeSiam { "
                "	call NasiLemak; "
                "	while iceCream { "
                "		chilli = ayam + 100 - 20 * 5 + ketchup - egg; "
                "		egg = ketchup - ayam + chilli; "
                "		while ayam { "
                "			while chilli { "
                "				while ketchup { "
                "					ketchup = 1 - 5 * 20; "
                "					oats = 9 + 100 - 20 + ketchup * 20; "
                "					ayam = 5 + 9 * 20; "
                "					ketchup = (1 - 5 * 20) - 100 * egg; "
                "				} "
                "			} "
                "			while ayam { "
                "				chilli = ketchup; "
                "				fish = 9 + 100 - 20 + ketchup * 20; "
                "				egg = 100 * 2 - date * 20; "
                "				chilli = chilli; "
                "				chilli = chilli + ketchup * 20; "
                "				ayam = oats - 20 + 30 * (100 - 5 + egg) + 9 - 20 * 10; "
                "			} "
                "			ketchup = ayam + fish - 100 + 20 * 5 - 9 - 20 * 10; "
                "			ayam = ketchup + fish - 100 + 20 * 5; "
                "			while fish { "
                "				fish = fish; "
                "				fish = fish + fish; "
                "				fish = ketchup - egg * 5 + chilli - 20 * 9; "
                "			} "
                "		} "
                "	} "
                "	chilli = ketchup + (ayam - egg) + 5 * (100 - 20 + (chilli + egg - ketchup) + oats) - fish; "
                "	fish = chilli - ketchup + (ayam - egg) + 5 * (100 - 20); "
                "	call CharKwayTeow; "
                "} "
                " "
                "procedure CarrotCake { "
                "	ginger = iceCream + ketchup - chilli + jam * 5 - 9 + date - 100; "
                "	iceCream = ginger - ketchup + 9 - 5 * date - 100; "
                "	iceCream = chilli - 20 * 9; "
                "	chilli = 9 + 100 - 20 + ketchup * 20; "
                "	jam = chilli + egg - ketchup; "
                "	while jam { "
                "		while egg { "
                "			while jam { "
                "				if egg then { "
                "					egg = ketchup - egg * 5; "
                "					call MeeSiam; "
                "					jam = chilli + ketchup * 20; "
                "				} "
                "				else { "
                "					ketchup = egg * oats - jam + ginger; "
                "					while date { "
                "						date = ketchup - iceCream + ginger - 9 + 100 * 5; "
                "					} "
                "					egg = chilli + egg - ketchup; "
                "					ketchup = date + iceCream + 100 - 9; "
                "				} "
                "			} "
                "			if jam then { "
                "				ketchup = egg + chilli - ketchup; "
                "				egg = chilli + egg; "
                "				ginger = ginger - ketchup + 9; "
                "			} "
                "			else { "
                "				ketchup = ginger + chilli - 5 * 100 - 20 * egg; "
                "				date = jam + 20 + ketchup * 20; "
                "				while jam { "
                "					jam = ketchup + chilli * 20; "
                "					chilli = 20 * 10 + 9 - 100 * 20 - ketchup; "
                "				} "
                "				chilli = iceCream + 9 + 100 - 20 + ketchup; "
                "			} "
                "			while chilli { "
                "				iceCream = ketchup + chilli - 9 + 20 * 100; "
                "			} "
                "			iceCream = iceCream + ginger - jam; "
                "			call MalaHotpot; "
                "			call BakKutTeh; "
                "			jam = ketchup + 20 - 100; "
                "		} "
                "	} "
                "} "
                " "
                "procedure MalaHotpot { "
                "	iceCream = pea - lime * 100 - 20 + honey * fish; "
                "	pea = lime + 20 - 5 * fish + pea; "
                "	lime = 20 * 100 + fish; "
                "	iceCream = iceCream * 100 - 2 + 9 * 100; "
                "	pea = lime - iceCream + fish - 20 * 100; "
                "	while lime { "
                "		if pea then { "
                "			while lime { "
                "				if pea then { "
                "					lime = iceCream + lime - pea + fish * 20; "
                "					fish = 20 * lime - 2 + 50 - 9 + 1; "
                "					call BakKutTeh; "
                "					lime = iceCream + fish - pea - 20 + 100; "
                "					pea = iceCream + 10; "
                "				} "
                "				else { "
                "					pea = lime - 10 + 100 - fish; "
                "					fish = pea + lime - 100 * 20 + 5 - iceCream; "
                "					call BeeHoon; "
                "					fish = pea + 100 - 5 * 20 + 9 + iceCream; "
                "				} "
                "			} "
                "		} "
                "		else { "
                "			honey = honey + 20 - 100 * fish; "
                "			while honey { "
                "				fish = honey + 20 + iceCream + 10; "
                "			} "
                "			honey = fish - pea - 20; "
                "			if fish then { "
                "				honey = fish - 2 + 50 - 9 + 1; "
                "			} "
                "			else { "
                "				iceCream = honey * (lime - iceCream); "
                "			} "
                "			pea = 9 + iceCream; "
                "			call CurryFishHead; "
                "			pea = lime + iceCream - 10; "
                "		} "
                "	} "
                "	iceCream = pea + lime + iceCream - 10; "
                "	call Bingsu; "
                "} "
                " "
                "procedure WantonMee { "
                "	mushroom = nutmeg + broccoli + ayam - 100 * 9 - 20 + oats - 100 * 5 + date - pea; "
                "	broccoli = ayam - 100 * 9 - 20; "
                "	oats = broccoli + nutmeg + broccoli + ayam - 100 * 9; "
                "	pea = pea + oats - nutmeg + broccoli + ayam - 100 * 9; "
                "	call CurryFishHead; "
                "	date = (date * 10) - 5; "
                "	mushroom = mushroom + fish * 10 - broccoli * 100 + ayam; "
                "	ayam = oats * 9 - pea * 5 + ayam; "
                "	while ayam { "
                "		oats = pea + oats - broccoli + ayam; "
                "		oats = oats - 100 * 9; "
                "		broccoli = 9 - 20 + oats - 100 * 5; "
                "	} "
                "	call Bingsu; "
                "	broccoli = mushroom + nutmeg + ayam; "
                "	nutmeg = nutmeg + broccoli + ayam - 100 * 9; "
                "} "
                " "
                "procedure Rojak { "
                "	iceCream = honey + chilli - 100 * 5 + fish + 9 - 20 - date; "
                "	fish = iceCream + honey - chilli * 5 - fish + 9 - 20; "
                "	honey = fish - 100; "
                "	while fish { "
                "		iceCream = honey + fish - 100 * 5 + fish - 20; "
                "		date = 100 * 5 + fish - date; "
                "		while honey { "
                "			honey = chilli - 100 * 20 + date - iceCream; "
                "			iceCream = chilli + 20 * 100; "
                "			fish = iceCream + date - honey; "
                "		} "
                "		iceCream = honey + chilli - fish; "
                "	} "
                "	call WantonMee; "
                "	honey = fish * 100 - date; "
                "	call Bingsu; "
                "	if date then { "
                "		iceCream = fish + honey; "
                "	} "
                "	else { "
                "		iceCream = chilli + 20 + 10 * 5 - 9; "
                "	} "
                "	call Takoyaki; "
                "	chilli = iceCream + honey + chilli - fish; "
                "	fish = honey + chilli - 100 * 5; "
                "} "
                " "
                "procedure NasiLemak { "
                "	while honey { "
                "		call FriedRice; "
                "		while honey { "
                "			call FriedRice; "
                "			while honey { "
                "				call FriedRice; "
                "			} "
                "		} "
                "		while honey { "
                "			call FriedRice; "
                "		} "
                "	} "
                "	if honey then { "
                "		call BakKutTeh; "
                "		if honey then { "
                "			call BakKutTeh; "
                "		} "
                "		else { "
                "			call BakKutTeh; "
                "		} "
                "	} "
                "	else { "
                "		call BakKutTeh; "
                "	} "
                "} "
                " "
                "procedure CharKwayTeow { "
                "	ginger = fish + mushroom - 100 * 5 + nutmeg - egg; "
                "	fish = egg + 100 * 5 - 20 + nutmeg; "
                "	call FriedRice; "
                "	while nutmeg { "
                "		ginger = fish + 5 - nutmeg; "
                "	} "
                "	call McSpicy; "
                "	fish = ginger * 100 - 5; "
                "	egg = fish - 2 + 50 - 9 + 1; "
                "	call CurryFishHead; "
                "	ginger = egg + fish - 2 + 50 - 9 + 1; "
                "} "
                " "
                "procedure CurryFishHead { "
                "	chilli = broccoli + (5 - (9 * (chilli + ayam - 30) + 100 * 2 - date * 20)); "
                "	call Laksa; "
                "	broccoli = chilli + ayam - date; "
                "	ayam = date + chilli; "
                "} "
                " "
                "procedure Bingsu { "
                "	jam = nutmeg + broccoli + ayam - 100 * 9; "
                "	ketchup = nutmeg + broccoli + ayam - 100 * 9; "
                "	nutmeg = 100 * 9; "
                "	while nutmeg { "
                "		jam = nutmeg + broccoli + ayam - 100 * 9; "
                "		call BeeHoon; "
                "	} "
                "	if jam then { "
                "		ketchup = ayam - 100 * 9; "
                "		broccoli = nutmeg + broccoli; "
                "		call YongTauFoo; "
                "		call RotiPrata; "
                "		ayam = ayam - 100 * 9; "
                "	} "
                "	else { "
                "		jam = nutmeg + broccoli + ayam - 100 * 9; "
                "		ayam = nutmeg + broccoli; "
                "		call BeeHoon; "
                "		call HokkienMee; "
                "		nutmeg = 100 * 9; "
                "	} "
                "} "
                " "
                "procedure Takoyaki { "
                "	date = iceCream + chilli + 20 + 10 * 5 - 9; "
                "	call RotiPrata; "
                "	chilli = chilli + 20 + 10 * 5 - 9; "
                "} "
                " "
                "procedure BakKutTeh { "
                "	broccoli = fish + broccoli - egg * ginger; "
                "	egg = fish + ginger - 100 * 9; "
                "	ginger = 20 + 10 * 5 - 9 * iceCream; "
                "	call McSpicy; "
                "	call BeeHoon; "
                "	call HokkienMee; "
                "	ginger = broccoli + egg + fish - ginger * iceCream; "
                "} "
                " "
                "procedure FriedRice { "
                "	broccoli = fish + broccoli - egg * ginger; "
                "	fish = ginger * 9 + 100 - 20 + 1; "
                "	egg = broccoli + 20 * 9 - fish * ginger; "
                "	broccoli = ginger * 20; "
                "	egg = ginger; "
                "	fish = egg * 100 * 9 - 20; "
                "} "
                " "
                "procedure McSpicy { "
                "	ayam = broccoli + chilli; "
                "	call Zinger; "
                "	call Zinger; "
                "	chilli = ayam + broccoli - date; "
                "} "
                " "
                "procedure Zinger { "
                "	date = iceCream + fish; "
                "	fish = 20 + fish * 100; "
                "	ginger = 100 * 5; "
                "} "
                " "
                "procedure BeeHoon { "
                "	nutmeg = jam + ketchup - lime * 100 + 2; "
                "	call LorMee; "
                "	jam = lime - 100 * 9; "
                "	call Popiah; "
                "	lime = jam - nutmeg + 100 * 9; "
                "} "
                " "
                "procedure Laksa { "
                "	oats = pea + ketchup - chilli * 100 - 5 + 20; "
                "	call Zinger; "
                "	chilli = pea + 20 * (100 * 9); "
                "	call LorMee; "
                "	pea = ginger * honey - oats; "
                "	oats = lime + 5 + pea; "
                "	call Popiah; "
                "	lime = ketchup + pea; "
                "} "
                " "
                "procedure HokkienMee { "
                "	lime = (ayam - honey) * ginger; "
                "	honey = ayam * ginger + 100; "
                "	call LorMee; "
                "	honey = lime + ginger - ayam; "
                "	call Popiah; "
                "	ginger = lime * ayam; "
                "} "
                " "
                "procedure RotiPrata { "
                "	oats = 9 * (chilli + ayam - 30) + 100 * 2 - date * 20; "
                "	pea = 1 - 5 * 20; "
                "	call YongTauFoo; "
                "	ayam = oats + date; "
                "} "
                " "
                "procedure YongTauFoo { "
                "	fish = 5 - (9 * (chilli + ayam - 30) + 100 * 2 - date * 20) + (((1 - 5 * 20) - 100 * egg) + fish - ginger + broccoli) - (ayam - honey) * ginger - fish + 100 - 20 * 4; "
                "	call LorMee; "
                "	ginger = broccoli * (100 - 9); "
                "	broccoli = fish + (100 * 9); "
                "	call Popiah; "
                "	broccoli = fish + broccoli - 9; "
                "} "
                " "
                "procedure LorMee { "
                "	egg = iceCream + ginger * 5; "
                "	call Popiah; "
                "	chilli = fish - 10 + egg; "
                "} "
                " "
                "procedure Popiah { "
                "	ayam = broccoli * 9; "
                "	pea = ginger + honey * 5; "
                "	nutmeg = ayam + honey; "
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
