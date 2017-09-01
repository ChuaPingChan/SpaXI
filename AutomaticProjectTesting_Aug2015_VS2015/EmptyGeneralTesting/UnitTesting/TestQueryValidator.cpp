#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestQueryValidator)
    {
    public:

        TEST_METHOD(TestQueryEntityRegex)
        {
            QueryValidator qv;
            string input;
            
            //Valid Entities
            input = "procedure";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "stmtLst";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "stmt";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "assign";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "call";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "while";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "if";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "variable";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "constant";
            Assert::IsTrue(qv.isValidEntityTest(input));
            input = "prog_line";
            Assert::IsTrue(qv.isValidEntityTest(input));

            //Invalid Entities
            input = "invalidEntity";
            Assert::IsFalse(qv.isValidEntityTest(input));
            input = "invalidEntityEndsWith#";
            Assert::IsFalse(qv.isValidEntityTest(input));
            input = "invalidEntityEndsWith1";
            Assert::IsFalse(qv.isValidEntityTest(input));
            input = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidEntityTest(input));
            input = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidEntityTest(input));
        }

        TEST_METHOD(TestQuerySynonymRegex)
        {
            QueryValidator qv;
            string input;

            //Valid Synonym
            input = "a";
            Assert::IsTrue(qv.isValidSynonymTest(input));
            input = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(input));
            input = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(input));
            input = "nameWith#SymbolWithoutNumbers";
            Assert::IsTrue(qv.isValidSynonymTest(input));
            input = "nameW1thNumb3rAnd#Symbol";
            Assert::IsTrue(qv.isValidSynonymTest(input));
            

            //Invalid Synonym
            input = "0";
            Assert::IsFalse(qv.isValidSynonymTest(input));
            input = "#";
            Assert::IsFalse(qv.isValidSynonymTest(input));
            input = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qv.isValidSynonymTest(input));
            input = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidSynonymTest(input));
            input = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidSynonymTest(input));
        }

    };
}