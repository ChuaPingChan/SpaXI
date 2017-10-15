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

    TEST_CLASS(TestParserPopulatePkb)
    {
    public:

        const std::string dummySimpleSourcePath = "../UnitTesting/ParserTestDependencies/dummySimpleSource.txt";
        
        TEST_METHOD(bug1Test)
        {
            /*
            Bug description:
            Throws unknown exception when running system test on AutoTester.
            */
            // Set up
            PKBMain pkb;
            Parser parser(&pkb);
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<string> actualResults;
            list<string> expectedResults;

            string query =
                "variable v; while w; assign a; prog_line n; Select n such that Modifies(w,_) such that Uses (a,_)";
            PQLMain pql = PQLMain(query);

            actualResults = pql.run();
            expectedResults = list<string>{ "1", "2", "3", "4", "5", "6", "7" };
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*******************************
        * Utility Methods for Testing *
        *******************************/
        TEST_METHOD(testDummySimpleSourceFileUtilityMethods)
        {
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*
        This is a utility method to create a source file.
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
