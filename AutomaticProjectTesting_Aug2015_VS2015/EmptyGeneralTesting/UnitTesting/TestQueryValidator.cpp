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
            string str;
            
            //Valid Entities
            str = "procedure";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "stmtLst";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "stmt";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "assign";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "call";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "while";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "if";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "variable";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "constant";
            Assert::IsTrue(qv.isValidEntityTest(str));
            str = "prog_line";
            Assert::IsTrue(qv.isValidEntityTest(str));

            //Invalid Entities
            str = "invalidEntity";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "invalidEntityEndsWith#";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "invalidEntityEndsWith1";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidEntityTest(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidEntityTest(str));
        }

        TEST_METHOD(TestQuerySynonymRegex)
        {
            QueryValidator qv;
            string str;

            //Valid Synonym
            str = "a";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameWith#SymbolWithoutNumbers";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "nameW1thNumb3rAnd#Symbol";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            str = "assign";
            Assert::IsTrue(qv.isValidSynonymTest(str));
            

            //Invalid Synonym
            str = "0";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "#";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(qv.isValidSynonymTest(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(qv.isValidSynonymTest(str));
        }

        TEST_METHOD(TestQueryDeclarationValidity)
        {
            QueryValidator qv;
            string str;

            //Valid Declaration
            str = "assign validEntityAndSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity, multipleVa1idSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity  , separatedByComma ,      multipleValidSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "stmt validEntity, mixedCommaFormat     ,      multipleVa1idSynonym";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "variable          validEntitySynonymWithWhitespace";
            Assert::IsTrue(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "while \n validEntitySynonymWithNewline";
            Assert::IsTrue(qv.isValidDeclarationTest(str));

            //Invalid Declaration
            qv = QueryValidator();
            str = "invalidEntity inv@lidSyn0nym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "invalidEntity validSynonym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity, inv@lidSynonym";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity validSynonym  but no comma";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
            qv = QueryValidator();
            str = "assign validEntity, validSynonymRepeted, validSynonymRepeted";
            Assert::IsFalse(qv.isValidDeclarationTest(str));
        }

        TEST_METHOD(TestQuerySelectValidity)
        {
        }

        TEST_METHOD(TestQueryValidity)
        {
            QueryValidator qv;
            vector<string> inputVector;

            inputVector.push_back("assign a");
            inputVector.push_back("variable v");
            inputVector.push_back("Select v");

            Assert::IsTrue(qv.isValidQuery(inputVector));
        }


    };
}