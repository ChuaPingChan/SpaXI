//#include "CppUnitTest.h"
//#include "string.h"
//#include "..\..\SPA\PQL\QueryValidatorFriend.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//using namespace std;
//
//namespace UnitTesting
//{
//    TEST_CLASS(TestRegexBasic)
//    {
//    public:
//
//        /*********
//        * Letter *
//        *********/
//
//        TEST_METHOD(TestRegex_Letter_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "a";
//            Assert::IsTrue(qvf.isValidLetter(str));
//        }
//
//        TEST_METHOD(TestRegex_Letter_MultipleLetters_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "invalid";
//            Assert::IsFalse(qvf.isValidLetter(str));
//        }
//
//        TEST_METHOD(TestRegex_Letter_Alphanumerics_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "1nva1id";
//            Assert::IsFalse(qvf.isValidLetter(str));
//        }
//
//        TEST_METHOD(TestRegex_Letter_symbols_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "1nv@lid{#";
//            Assert::IsFalse(qvf.isValidLetter(str));
//        }
//
//
//
//        /**********
//        * Integer *
//        **********/
//
//        TEST_METHOD(TestRegex_Integer_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "1";
//            Assert::IsTrue(qvf.isValidInteger(str));
//            str = "0123";
//            Assert::IsTrue(qvf.isValidInteger(str));
//        }
//
//        TEST_METHOD(TestRegex_Integer_Alphanumeric_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "1nva1id";
//            Assert::IsFalse(qvf.isValidLetter(str));
//        }
//
//        TEST_METHOD(TestRegex_Integer_symbols_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "1nv@lid{#";
//            Assert::IsFalse(qvf.isValidLetter(str));
//        }
//        
//
//
//        /**********
//        * Synonym *
//        **********/
//
//        TEST_METHOD(TestRegex_Synonym_SingleLetter_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "a";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//        }
//
//        TEST_METHOD(TestRegex_Synonym_Alphanumeric_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "nameWithoutNumAndHexSymbol";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//            str = "nameW1thNumb3rW1th0utH3xSymbol";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//            str = "nameWith#SymbolWithoutNumbers";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//            str = "nameW1thNumb3rAnd#Symbol";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//        }
//
//        //TODO: Change to IsFalse after disallowing them to have the same name
//        TEST_METHOD(TestRegex_Synonym_SameNameAsDesignEntity_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "assign";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//        }
//
//        TEST_METHOD(TestRegex_Synonym_IncorrectStartingChar_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "0";
//            Assert::IsFalse(qvf.isValidSynonym(str));
//            str = "#";
//            Assert::IsFalse(qvf.isValidSynonym(str));
//        }
//
//        TEST_METHOD(TestRegex_Synonym_SpecialChar_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "n@meWithSpeci@lSymbols";
//            Assert::IsFalse(qvf.isValidSynonym(str));
//        }
//
//
//
//        /**********
//        * StmtRef *
//        **********/
//
//        TEST_METHOD(TestRegex_StmtRef_Synonym_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "validSynonym";
//            Assert::IsTrue(qvf.isValidStmtRef(str));
//        }
//
//        TEST_METHOD(TestRegex_StmtRef_Underscore_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "_";
//            Assert::IsTrue(qvf.isValidStmtRef(str));
//        }
//
//        TEST_METHOD(TestRegex_StmtRef_Integers_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "22011209040009142005070518";
//            Assert::IsTrue(qvf.isValidStmtRef(str));
//        }
//
//        TEST_METHOD(TestRegex_StmtRef_SpecialChar_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "validSynonym_validUnderscore_220112@@9040009142005070518";
//            Assert::IsFalse(qvf.isValidStmtRef(str));
//        }
//
//        TEST_METHOD(TestRegex_StmtRef_Ident_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "\"validIdentWithQuotationMarks\"";
//            Assert::IsFalse(qvf.isValidStmtRef(str));
//        }
//
//
//
//        /**********
//        * EntRef *
//        **********/
//
//        TEST_METHOD(TestRegex_EntRef_Synonym_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "validSynonym";
//            Assert::IsTrue(qvf.isValidEntRef(str));
//        }
//
//        TEST_METHOD(TestRegex_EntRef_Underscore_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "_";
//            Assert::IsTrue(qvf.isValidEntRef(str));
//        }
//
//        TEST_METHOD(TestRegex_EntRef_Ident_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "\"validIdentWithQuotationMarks\"";
//            Assert::IsTrue(qvf.isValidEntRef(str));
//        }
//
//        TEST_METHOD(TestRegex_EntRef_SpecialChar_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "validSynonym_validUnderscore_\"validIdentW1thQu0tationMarks\"";
//            Assert::IsFalse(qvf.isValidEntRef(str));
//        }
//
//
//
//        /*******
//        * Name *
//        *******/
//
//        TEST_METHOD(TestRegex_Name_SingleChar_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "a";
//            Assert::IsTrue(qvf.isValidName(str));
//        }
//
//        TEST_METHOD(TestRegex_Name_Alphanumeric_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "validName23";
//            Assert::IsTrue(qvf.isValidName(str));
//        }
//
//        //TODO: Change to IsFalse after disallowing them to have the same name
//        TEST_METHOD(TestRegex_Name_SameNameAsDesignEntity_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "assign";
//            Assert::IsTrue(qvf.isValidSynonym(str));
//        }
//
//        TEST_METHOD(TestRegex_Name_Integer_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "0";
//            Assert::IsFalse(qvf.isValidName(str));
//        }
//
//        TEST_METHOD(TestRegex_Name_WithSpecialChar_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "n@meWithSpeci@lSymbols";
//            Assert::IsFalse(qvf.isValidName(str));
//            str = "1invalidEntityStartsWithNumber";
//            Assert::IsFalse(qvf.isValidName(str));
//        }
//
//
//
//        /****************
//        * Design Entity *
//        ****************/
//        TEST_METHOD(TestRegex_DesignEntity_Procedure_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "procedure";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_StmtLst_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "stmtLst";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Stmt_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "stmt";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Assign_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "assign";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Call_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "call";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_While_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "while";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_If_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "if";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Variable_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "variable";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Constant_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "constant";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_ProgLine_Valid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "prog_line";
//            Assert::IsTrue(qvf.isValidEntity(str));
//        }
//
//        TEST_METHOD(TestRegex_DesignEntity_Invalid)
//        {
//            QueryValidatorFriend qvf;
//            string str = "invalidEntity";
//            Assert::IsFalse(qvf.isValidEntity(str));
//            str = "invalidEntityEndsWith#";
//            Assert::IsFalse(qvf.isValidEntity(str));
//            str = "invalidEntityEndsWith1";
//            Assert::IsFalse(qvf.isValidEntity(str));
//            str = "1invalidEntityStartsWithNumber";
//            Assert::IsFalse(qvf.isValidEntity(str));
//            str = "#invalidEntityStartsWithSymbol";
//            Assert::IsFalse(qvf.isValidEntity(str));
//        }
//
//    };
//}
