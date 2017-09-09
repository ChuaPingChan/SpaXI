#include <string>
#include <cstdio>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestParser)
    {
    public:

        TEST_METHOD(getTokenTest_inputFile_tokenizedCorrectly)
        {
            Parser parser;
            std::string newFilePath("../UnitTesting/ParserTestDependencies/getTokenInput.txt");
            std::ofstream outfile(newFilePath);
            
            std::string inputString("procedure F1rst {\n  a =10;\n while i {\n c = 20;}}\n");
            outfile << inputString;
            outfile.close(); 
            
            std::string expectedTokenArray[16] = { "procedure", "F1rst", "{", "a", "=", "10", ";", "while", "i", "{", "c", "=", "20", ";", "}", "}" };
            std::vector<std::string> expectedTokens(expectedTokenArray, expectedTokenArray + sizeof(expectedTokenArray) / sizeof(expectedTokenArray[0]));
            std::vector<std::string> actualTokens = parser.getTokenTest(newFilePath);


            // Remove file created
            Assert::IsTrue(std::remove(newFilePath.c_str()) == 0);
            Assert::IsTrue(expectedTokens == actualTokens);
        }

    };
}