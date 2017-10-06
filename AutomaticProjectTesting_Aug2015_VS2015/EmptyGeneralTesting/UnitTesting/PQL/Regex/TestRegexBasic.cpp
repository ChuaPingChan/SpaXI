#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexBasic)
    {
    public:

        /*********
        * Letter *
        *********/

        TEST_METHOD(TestRegex_Letter_Valid)
        {
            string str = "a";
            Assert::IsTrue(RegexValidators::isValidLetterRegex(str));
        }

        TEST_METHOD(TestRegex_Letter_MultipleLetters_Invalid)
        {
            string str = "invalid";
            Assert::IsFalse(RegexValidators::isValidLetterRegex(str));
        }

        TEST_METHOD(TestRegex_Letter_Alphanumerics_Invalid)
        {
            string str = "1nva1id";
            Assert::IsFalse(RegexValidators::isValidLetterRegex(str));
        }

        TEST_METHOD(TestRegex_Letter_symbols_Invalid)
        {
            string str = "1nv@lid{#";
            Assert::IsFalse(RegexValidators::isValidLetterRegex(str));
        }



        /**********
        * Integer *
        **********/

        TEST_METHOD(TestRegex_Integer_Valid)
        {
            string str = "1";
            Assert::IsTrue(RegexValidators::isValidIntegerRegex(str));
            str = "0123";
            Assert::IsTrue(RegexValidators::isValidIntegerRegex(str));
        }

        TEST_METHOD(TestRegex_Integer_Alphanumeric_Invalid)
        {
            string str = "1nva1id";
            Assert::IsFalse(RegexValidators::isValidIntegerRegex(str));
        }

        TEST_METHOD(TestRegex_Integer_symbols_Invalid)
        {
            string str = "1nv@lid{#";
            Assert::IsFalse(RegexValidators::isValidIntegerRegex(str));
        }
        


        /**********
        * Synonym *
        **********/

        TEST_METHOD(TestRegex_Synonym_SingleLetter_Valid)
        {
            string str = "a";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
        }

        TEST_METHOD(TestRegex_Synonym_Alphanumeric_Valid)
        {
            string str = "nameWithoutNumAndHexSymbol";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
            str = "nameW1thNumb3rW1th0utH3xSymbol";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
            str = "nameWith#SymbolWithoutNumbers";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
            str = "nameW1thNumb3rAnd#Symbol";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
        }

        TEST_METHOD(TestRegex_Synonym_SameNameAsDesignEntity_Valid)
        {
            string str = "assign";
            Assert::IsTrue(RegexValidators::isValidSynonymRegex(str));
        }

        TEST_METHOD(TestRegex_Synonym_IncorrectStartingChar_Invalid)
        {
            string str = "0";
            Assert::IsFalse(RegexValidators::isValidSynonymRegex(str));
            str = "#";
            Assert::IsFalse(RegexValidators::isValidSynonymRegex(str));
        }

        TEST_METHOD(TestRegex_Synonym_SpecialChar_Invalid)
        {
            string str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(RegexValidators::isValidSynonymRegex(str));
        }



        /**********
        * StmtRef *
        **********/

        TEST_METHOD(TestRegex_StmtRef_Synonym_Valid)
        {
            string str = "validSynonym";
            Assert::IsTrue(RegexValidators::isValidStmtRefRegex(str));
        }

        TEST_METHOD(TestRegex_StmtRef_Underscore_Valid)
        {
            string str = "_";
            Assert::IsTrue(RegexValidators::isValidStmtRefRegex(str));
        }

        TEST_METHOD(TestRegex_StmtRef_Integers_Valid)
        {
            string str = "22011209040009142005070518";
            Assert::IsTrue(RegexValidators::isValidStmtRefRegex(str));
        }

        TEST_METHOD(TestRegex_StmtRef_SpecialChar_Invalid)
        {
            string str = "validSynonym_validUnderscore_220112@@9040009142005070518";
            Assert::IsFalse(RegexValidators::isValidStmtRefRegex(str));
        }

        TEST_METHOD(TestRegex_StmtRef_Ident_Invalid)
        {
            string str = "\"validIdentWithQuotationMarks\"";
            Assert::IsFalse(RegexValidators::isValidStmtRefRegex(str));
        }



        /**********
        * EntRef *
        **********/

        TEST_METHOD(TestRegex_EntRef_Synonym_Valid)
        {
            string str = "validSynonym";
            Assert::IsTrue(RegexValidators::isValidEntRefRegex(str));
        }

        TEST_METHOD(TestRegex_EntRef_Underscore_Valid)
        {
            string str = "_";
            Assert::IsTrue(RegexValidators::isValidEntRefRegex(str));
        }

        TEST_METHOD(TestRegex_EntRef_Ident_Valid)
        {
            string str = "\"validIdentWithQuotationMarks\"";
            Assert::IsTrue(RegexValidators::isValidEntRefRegex(str));
        }

        TEST_METHOD(TestRegex_EntRef_SpecialChar_Invalid)
        {
            string str = "validSynonym_validUnderscore_\"validIdentW1thQu0tationMarks\"";
            Assert::IsFalse(RegexValidators::isValidEntRefRegex(str));
        }



        /*******
        * Name *
        *******/

        TEST_METHOD(TestRegex_Name_SingleChar_Valid)
        {
            string str = "a";
            Assert::IsTrue(RegexValidators::isValidNameRegex(str));
        }

        TEST_METHOD(TestRegex_Name_Alphanumeric_Valid)
        {
            string str = "validName23";
            Assert::IsTrue(RegexValidators::isValidNameRegex(str));
        }

        TEST_METHOD(TestRegex_Name_Integer_Invalid)
        {
            string str = "0";
            Assert::IsFalse(RegexValidators::isValidNameRegex(str));
        }

        TEST_METHOD(TestRegex_Name_WithSpecialChar_Invalid)
        {
            
            string str = "n@meWithSpeci@lSymbols";
            Assert::IsFalse(RegexValidators::isValidNameRegex(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(RegexValidators::isValidNameRegex(str));
        }



        /****************
        * Design Entity *
        ****************/
        TEST_METHOD(TestRegex_DesignEntity_Procedure_Valid)
        {
            
            string str = "procedure";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_StmtLst_Valid)
        {
            
            string str = "stmtLst";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Stmt_Valid)
        {
            
            string str = "stmt";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Assign_Valid)
        {
            
            string str = "assign";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Call_Valid)
        {
            
            string str = "call";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_While_Valid)
        {
            
            string str = "while";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_If_Valid)
        {
            
            string str = "if";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Variable_Valid)
        {
            
            string str = "variable";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Constant_Valid)
        {
            
            string str = "constant";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_ProgLine_Valid)
        {
            
            string str = "prog_line";
            Assert::IsTrue(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_Invalid)
        {
            
            string str = "invalidEntity";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "invalidEntityEndsWith#";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "invalidEntityEndsWith1";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
        }

    };
}
