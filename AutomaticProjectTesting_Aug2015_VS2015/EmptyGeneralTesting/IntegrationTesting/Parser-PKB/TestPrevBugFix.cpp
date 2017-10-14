#include <string>
#include <cstdio>
#include <regex>

#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"
#include "../SPA/PKB/PKBMain.h"
#include "../SPA/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const std::string dummySimpleSourcePath = "../IntegrationTesting/ParserTestDependencies/dummySimpleSource.txt";
PKBMain dummyPkbMain;
PKBMain* dummyPkbMainPtr = &dummyPkbMain;

namespace UnitTesting
{

    TEST_CLASS(TestPrevBugFix)
    {
    public:
        TEST_METHOD(TestBug1Fix)
        {
            // Set up
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_bug1());

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            list<int> expectedResults = list<int>{ 3, 5, 6, 7 };
            list<int> actualResults = dummyPkbMain.getAllChildren(Entity::STMT);
            expectedResults.sort();
            actualResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*******************************
         * Utility Methods for Testing *
         *******************************/
        TEST_METHOD(testDummySimpleSourceFileUtilityMethods)
        {
            Assert::IsTrue(createDummySimpleSourceFile_bug1());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only.
        */
        bool createDummySimpleSourceFile_bug1() {
            std::string content = "procedure One { \n	a = a + b + c + c + b + a; \n	while c { \n		c = a + b; \n	} \n	while c { \n		while b { \n			a = a + b + c + c + b + a; \n			b = b + b; \n		} \n	} \n}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        // This is a utility method to destroy the dummy text file created by createDummyTextFile()
        bool deleteDummySimpleSourceFile() {
            std::string newFilePath(dummySimpleSourcePath);
            return std::remove(newFilePath.c_str()) == 0;
        }
    };
}
