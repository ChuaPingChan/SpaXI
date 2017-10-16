#include <string>
#include <cstdio>
#include <regex>

#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"
#include "../SPA/PKB/PKBMain.h"
#include "../SPA/Entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestPrevBugFix)
    {
        const std::string dummySimpleSourcePath = "../IntegrationTesting/ParserTestDependencies/dummySimpleSource.txt";

    public:
        TEST_METHOD(TestBug1Fix)
        {
            /*
            Bug description:
            PKB uses indexing on hashmap to check for existence of entries. Therefore, when
            a key is not present, the key is added to hashmaps, which is wrong.
            */
            
            // Set up
            PKBMain dummyPkbMain;
            PKBMain* dummyPkbMainPtr = &dummyPkbMain;
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            list<int> expectedResults;
            list<int> actualResults;

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));
            
            actualResults = dummyPkbMain.getAllChildren(Entity::STMT);
            expectedResults = list<int>{ 3, 5, 6, 7 };
            expectedResults.sort();
            actualResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            dummyPkbMain.getParent(1, Entity::STMT);

            actualResults = dummyPkbMain.getAllChildren(Entity::STMT);
            expectedResults = list<int>{ 3, 5, 6, 7 };
            expectedResults.sort();
            actualResults.sort();
            Assert::IsTrue(actualResults == expectedResults);

            // Clean up
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        TEST_METHOD(TestBug2Fix)
        {
            /*
            Bug description:
            Set procedure Uses relation is not working properly for statements inside container variables.
            */

            // Set up
            PKBMain dummyPkbMain;
            PKBMain* dummyPkbMainPtr = &dummyPkbMain;
            Parser parser(dummyPkbMainPtr);
            Assert::IsTrue(createDummySimpleSourceFile_bug2());
            list<int> expectedResults;
            list<int> actualResults;

            Assert::IsTrue(parser.parse(dummySimpleSourcePath));

            actualResults = dummyPkbMain.getUsesFromProc(0);
            list<string> expectedStringList = list<string>{ "f", "h", "a" };
            expectedResults = dummyPkbMain.convertStringToIdx(expectedStringList, Entity::VARIABLE);
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
            Assert::IsTrue(createDummySimpleSourceFile_SimpleTest3());
            Assert::IsTrue(deleteDummySimpleSourceFile());
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only.
        */
        bool createDummySimpleSourceFile_SimpleTest3() {
            std::string content = "procedure One { \n	a = a + b + c + c + b + a; \n	while c { \n		c = a + b; \n	} \n	while c { \n		while b { \n			a = a + b + c + c + b + a; \n			b = b + b; \n		} \n	} \n}";
            std::string newFilePath(dummySimpleSourcePath);
            std::ofstream outfile(newFilePath);
            std::string inputString(content);
            outfile << inputString;
            outfile.close();
            return true;
        }

        /*
        This is a utility method to create a dummy text
        containing assignment statements only.
        */
        bool createDummySimpleSourceFile_bug2() {
            std::string content = "procedure Four { while f { g = 2 * h + (3 * 5) - 14 + 100 * a; } }";
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
