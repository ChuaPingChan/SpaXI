#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexDeclaration)
    {
    public:
        /********************
        * Declaration Regex *
        ********************/
        TEST_METHOD(TestRegex_Declaration_SingleSynonym_Valid)
        {
            string str = "stmt s";
            Assert::IsTrue(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_Whitespaces_Valid)
        {
            string str = "    stmt    s       ";
            Assert::IsTrue(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_BadArrangement_Invalid)
        {
            string str = "  s   stmt         ";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_RedundantComma_Invalid)
        {
            string str = " stmt s, ";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_NoSynonym_Invalid)
        {
            string str = "    assign        ";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_ValidEntity_Concatenate_ValidSynonym_Invalid)
        {
            string str = "    assignassign        ";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_NoEntity_Invalid)
        {
            string str = "  synonym      ";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_MultipleSynonym_MissingComma_Invalid)
        {
            string str = "stmt s1 s2 s3, s4, s5";
            Assert::IsFalse(RegexValidators::isValidDeclarationExtractedRegex(str));
        }
    };
}
