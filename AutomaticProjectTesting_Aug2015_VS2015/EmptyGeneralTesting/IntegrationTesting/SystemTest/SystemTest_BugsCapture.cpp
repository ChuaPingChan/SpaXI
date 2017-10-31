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
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest2());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "variable v, v1; assign a; stmt s; procedure p;"
                "Select v with p.procName = \"eight\" such that "
                "Uses(p,v) and Modifies(a,v1) with v1.varName = \"eC\" "
                "such that Uses(a,v) and Follows(_,a) and Follows*(_,a)";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "eD", "eA", "eC", "eB" };
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
        This is a utility method to create a source file for test 13.
        */
        bool createDummySimpleSourceFile_SimpleTest4() {
            std::string content =
                "procedure toCallFirst{\n"
                "	call first;\n"
                "}\n"
                "\n"
                "procedure first{\n"
                "	fA = fB;\n"
                "	call second;\n"
                "	fA = fA - fA + fA;\n"
                "\n"
                "	while fE {\n"
                "		fX = fX+10;\n"
                "		if fY then{\n"
                "			fStart = fEnd + fX -fY *(fA+fB);\n"
                "			while fX {\n"
                "				fX = fZ *14;\n"
                "				fX = 11 + fY;\n"
                "			}\n"
                "			fEnd = fStart;\n"
                "			fY = fY -8;\n"
                "			call third;\n"
                "		}\n"
                "		else {\n"
                "			fStart = fEnd;\n"
                "			fY = fY +5;\n"
                "\n"
                "			if fStart then {\n"
                "				fEnd = fStart * 99;\n"
                "			}\n"
                "			else {\n"
                "				fEnd = fA + fB - fC;\n"
                "			}\n"
                "			call singleAssignProc;\n"
                "		}\n"
                "		fA = fB + fC;\n"
                "	}\n"
                "	fA = fB*fC*fA -    fA + fC;\n"
                "	fB = fB - 24 * 10;\n"
                "	fC = fX +(fA - fB);\n"
                "	while fA{\n"
                "		fA = fA *10;\n"
                "		fC = fA -fB - fC;\n"
                "		call second;\n"
                "		call third;\n"
                "\n"
                "		fD = fA + fStart;\n"
                "		if fD then {\n"
                "			fD = 100;\n"
                "			while fE	{\n"
                "				fE = fF - fD;\n"
                "				fF = fE -(fD-fD)+fD;\n"
                "				if fH then {\n"
                "					fE = fA*fB;\n"
                "				}\n"
                "				else {\n"
                "					fD = fD-1 -1 -2;\n"
                "					if fZ then {\n"
                "						fB = fB*22 - fA;\n"
                "\n"
                "					}\n"
                "					else {\n"
                "						fJ = fJ -1 +fStart;\n"
                "					}\n"
                "				}\n"
                "				fEnd = fStart;\n"
                "			}\n"
                "		}\n"
                "		else {\n"
                "			call singleAssignProc;\n"
                "		}\n"
                "	}\n"
                "}\n"
                "\n"
                "procedure second {\n"
                "	sA = sB;\n"
                "	while sA{\n"
                "		sB = sA + sD;\n"
                "		while sB {\n"
                "			while sC {\n"
                "				while sD{\n"
                "					sC = sE + sA * sB;\n"
                "					sE = sC - sC *(sA - sB -sC * sC + sC);\n"
                "				}\n"
                "			}\n"
                "			sA = sD + (sC + (sC + (sC - (sC - (sC + sC)))) - sC);\n"
                "		}\n"
                "	}\n"
                "	call eight;\n"
                "	sB = sB;\n"
                "	sD = sD + sD;\n"
                "	sD  = sA - sD;\n"
                "	call singleAssignProc;\n"
                "}\n"
                "\n"
                "procedure third {\n"
                "	tA = 1;\n"
                "	fB = 000000000000000000000;\n"
                "\n"
                "	tB = 100 * 100 - 100 + 100 *(14 +(20 *(3 + 3)));\n"
                "	tB = 0 * 100;\n"
                "	tB = 0 - 1;\n"
                "\n"
                "	tB = tB * 100 - tA;\n"
                "	tB = tA * tA * (tB - tA);\n"
                "	tB = tB;\n"
                "	tB = 2;\n"
                "	call eight;\n"
                "	tC = tA * tA;\n"
                "	tD = tA - tC - tB;\n"
                "}\n"
                "\n"
                "procedure eight {\n"
                "	tA = 1;\n"
                "	sB = 1;\n"
                "\n"
                "	eA = eB + eC + eD - eF + eG + eH + eI*      eF + eZ ;\n"
                "	eC = eD*(eA)-(eC);\n"
                "	eA = eA -(eC*eD -eB);\n"
                "	eB = eB;\n"
                "	eC = eB * eA * eB - eA - eA - eA;\n"
                "	if eC then{\n"
                "		eC = eB -eA;\n"
                "		while eA {\n"
                "			eA = eA -eC;\n"
                "		}\n"
                "	}\n"
                "	else {\n"
                "		eA = eA - eC;\n"
                "	}\n"
                "	eB = eB  + eA;\n"
                "}\n"
                "\n"
                "procedure notCalledByAnyone {\n"
                "	notA = notB;\n"
                "	notC = notC*notA*notB-notB-(notE-notA)*(notB*notB);\n"
                "	while notK {\n"
                "		notA = notK;\n"
                "		while notB{\n"
                "			while notC {\n"
                "				notX = notY- notZ;\n"
                "			}\n"
                "			notC = notC;\n"
                "			notC = notC;\n"
                "			notC = notX;\n"
                "			while notX {\n"
                "				notX = notY*notZ-notE+(notB*notA-notA+notB);\n"
                "				while notX{\n"
                "					while notE{\n"
                "						notE = notA - notB - notC;\n"
                "						while notC{\n"
                "							while notB{\n"
                "								while notY{\n"
                "									while notZ{\n"
                "										notZ = notA -1;\n"
                "										notB = 100;\n"
                "										notA = 1 - 1 - 1 * notB;\n"
                "										notK = 2;\n"
                "									}\n"
                "								}\n"
                "							}\n"
                "							if notC then{\n"
                "								notC = notA + notA;\n"
                "								while notC{\n"
                "									notB = notC -                  notB;\n"
                "									notC  = notA - notA + notA + notD;\n"
                "								}\n"
                "								notB =113 - 100 *(100 - 100 +(1 - 2));\n"
                "							}\n"
                "							else {\n"
                "								notX = notY - notZ - notZ;\n"
                "								notZ = notY;\n"
                "								notY = notX + notZ * notY;\n"
                "							}\n"
                "						}\n"
                "					}\n"
                "					call singleAssignProc;\n"
                "					call singleStmt	;\n"
                "				}\n"
                "			}\n"
                "		}\n"
                "	}\n"
                "}\n"
                "\n"
                "procedure singleAssignProc {\n"
                "	a = a;\n"
                "}\n"
                "\n"
                "procedure singleStmt{\n"
                "    call noNesting;\n"
                "}\n"
                "\n"
                "procedure noNesting{\n"
                "    b = b;\n"
                "    c = c;\n"
                "    b = d;\n"
                "    call whileWithDummyNode;\n"
                "}\n"
                "\n"
                "procedure whileNoDummyNode{\n"
                "    while red {\n"
                "        black = red * black - green;\n"
                "        black = 2;\n"
                "        red = green;\n"
                "    }\n"
                "}\n"
                "\n"
                "procedure unrelatedProcedure{\n"
                "    while lame {\n"
                "        haha = LEL;\n"
                "        heHEHEHEHe = haha + LEL - rolf;\n"
                "        KEKEKEKE = joke - haha *(LEL - LOL);\n"
                "    }\n"
                "    LEL = joke;\n"
                "	call nestedIfStatements;\n"
                "}\n"
                "\n"
                "procedure nestedIfStatements{\n"
                "    if lancer then {\n"
                "        if impreza then {\n"
                "            gallardo = lancer - impreza;\n"
                "            if murceiago then {\n"
                "                if quattroporte then {\n"
                "                    quattroporte = quattroporte - impreza;\n"
                "                }\n"
                "                else {\n"
                "                    lancer = lancer+1;\n"
                "                }\n"
                "            }\n"
                "            else {\n"
                "                gallardo = gallardo;\n"
                "            }\n"
                "        }\n"
                "        else {\n"
                "			murceiago = gallardo;\n"
                "        }\n"
                "    }\n"
                "    else {\n"
                "        murceiago = lancer*quattroporte-gallardo;\n"
                "    }\n"
                "\n"
                "	if mustang then {\n"
                "            mustang = p1 + lancer;\n"
                "    }\n"
                "	else {\n"
                "		if p1 then {\n"
                "            if quattroporte then {\n"
                "                California = California;\n"
                "            }\n"
                "            else {\n"
                "                p1 = p1;\n"
                "            }}\n"
                "        else {\n"
                "                murceiago = mustang*p1;\n"
                "        }\n"
                "		p1 = p1;\n"
                "	}\n"
                "\n"
                "	a = b;\n"
                "	b = 1;\n"
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
