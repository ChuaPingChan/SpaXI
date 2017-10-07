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



        /************
        * Attr Name *
        ************/
        TEST_METHOD(TestRegex_AttrName_ProcName_Valid)
        {
            string str = "procName";
            Assert::IsTrue(RegexValidators::isValidAttrNameRegex(str));
        }

        TEST_METHOD(TestRegex_AttrName_VarName_Valid)
        {
            string str = "varName";
            Assert::IsTrue(RegexValidators::isValidAttrNameRegex(str));
        }

        TEST_METHOD(TestRegex_AttrName_Value_Valid)
        {
            string str = "value";
            Assert::IsTrue(RegexValidators::isValidAttrNameRegex(str));
        }

        TEST_METHOD(TestRegex_AttrName_StmtNum_Valid)
        {
            string str = "stmt#";
            Assert::IsTrue(RegexValidators::isValidAttrNameRegex(str));
        }



        /***********
        * Attr Ref *
        ***********/
        TEST_METHOD(TestRegex_AttrRef_Synonym_ProcName_Valid)
        {
            string str = "p.procName";
            Assert::IsTrue(RegexValidators::isValidAttrRefRegex(str));
        }

        TEST_METHOD(TestRegex_AttrRef_Synonym_VarName_Valid)
        {
            string str = "v.varName";
            Assert::IsTrue(RegexValidators::isValidAttrRefRegex(str));
        }

        TEST_METHOD(TestRegex_AttrRef_Synonym_Vale_Valid)
        {
            string str = "v.value";
            Assert::IsTrue(RegexValidators::isValidAttrRefRegex(str));
        }

        TEST_METHOD(TestRegex_AttrRef_Synonym_StmtNum_Valid)
        {
            string str = "s1.stmt#";
            Assert::IsTrue(RegexValidators::isValidAttrRefRegex(str));
        }

        TEST_METHOD(TestRegex_AttrRef_Whitespaces_Invalid)
        {
            string str = "  p   .    procName   ";
            Assert::IsFalse(RegexValidators::isValidAttrRefRegex(str));
        }

        TEST_METHOD(TestRegex_AttrRef_IllegalCharacters_Invalid)
        {
            string str = "s.stmt@";
            Assert::IsFalse(RegexValidators::isValidAttrRefRegex(str));
        }



        /*******
        * Elem *
        *******/
        TEST_METHOD(TestRegex_Elem_Synonym_Valid)
        {
            string str = "validSynonym";
            Assert::IsTrue(RegexValidators::isValidElemRegex(str));
        }

        TEST_METHOD(TestRegex_Elem_AttrRef_Valid)
        {
            string str = "p.procName";
            Assert::IsTrue(RegexValidators::isValidElemRegex(str));
        }



        /********
        * Tuple *
        ********/
        TEST_METHOD(TestRegex_Tuple_Elem_AttrRef_Valid)
        {
            string str = "p.procName";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_SingleElem_Valid)
        {
            string str = "<s>";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_MultipleElem_Two_Valid)
        {
            string str = "<s,s1>";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_MultipleElem_Three_Valid)
        {
            string str = "<s,s1,s2>";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_SingleElem_WhitespacesValid)
        {
            string str = "   <  s   >     ";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_MultipleElem_Whitespaces_Valid)
        {
            string str = "   <   s   ,  s1   >   ";
            Assert::IsTrue(RegexValidators::isValidTupleRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_EmptyElem_Invalid)
        {
            string str = " < > ";
            Assert::IsFalse(RegexValidators::isValidTupleRegex(str));
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

        TEST_METHOD(TestRegex_DesignEntity_IncorrectName_Invalid)
        {
            string str = "invalidEntity";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_IllegalChar_Ending_Invalid)
        {
            string str = "invalidEntityEndsWith#";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "invalidEntityEndsWith1";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
        }

        TEST_METHOD(TestRegex_DesignEntity_IllegalChar_Beginning_Invalid)
        {
            string str = "1invalidEntityStartsWithNumber";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
            str = "#invalidEntityStartsWithSymbol";
            Assert::IsFalse(RegexValidators::isValidEntityRegex(str));
        }



        /************
        * Result Cl *
        ************/
        TEST_METHOD(TestRegex_ResultCl_Tuple_Valid)
        {
            string str = "<s1, a , w>";
            Assert::IsTrue(RegexValidators::isValidResultClRegex(str));
        }

        TEST_METHOD(TestRegex_ResultCl_Boolean_Valid)
        {
            string str = "BOOLEAN";
            Assert::IsTrue(RegexValidators::isValidResultClRegex(str));
        }




        /************
        * Rel Cond *
        ************/
        TEST_METHOD(TestRegex_RelCond_ClauseCount_One_Valid)
        {
            string str = "Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidRelCondRegex(str));
        }

        TEST_METHOD(TestRegex_RelCond_ClauseCount_Two_Valid)
        {
            string str = " Follows(1,2) and Parent(1,2) ";
            Assert::IsTrue(RegexValidators::isValidRelCondRegex(str));
        }

        TEST_METHOD(TestRegex_RelCond_ClauseCount_Multiple_Valid)
        {
            string str = " Follows(1, 2) and Parent(1, 2) and Modifies(1, v) and Uses(1, v) and Follows*(2, 3) and Parent*(2, 3) ";
            Assert::IsTrue(RegexValidators::isValidRelCondRegex(str));
        }

        TEST_METHOD(TestRegex_RelCond_Whitespaces_Valid)
        {
            string str = "  Follows  (   1     ,           2         )     and       Parent     (     1      ,     2     )  ";
            Assert::IsTrue(RegexValidators::isValidRelCondRegex(str));
        }

        TEST_METHOD(TestRegex_RelCond_MissingWhitespace_Invalid)
        {
            string str = "Follows(1,2)andParent(1,2)";
            Assert::IsFalse(RegexValidators::isValidRelCondRegex(str));
        }




        /***************
        * Such That Cl *
        ***************/
        TEST_METHOD(TestRegex_SuchThatCl_ClauseCount_One_Valid)
        {
            string str = "such that Follows(1, 2)";
            Assert::IsTrue(RegexValidators::isValidSuchThatClRegex(str));
        }

        TEST_METHOD(TestRegex_SuchThatCl_ClauseCount_Two_Valid)
        {
            string str = "such that Follows(1, 2) and Parent(1, 2)";
            Assert::IsTrue(RegexValidators::isValidSuchThatClRegex(str));
        }

        TEST_METHOD(TestRegex_SuchThatCl_ClauseCount_Multiple_Valid)
        {
            string str = "such that Follows(1, 2) and Parent(1, 2) and Modifies(1, v) and Uses(1, v) and Follows*(2, 3) and Parent*(2, 3)";
            Assert::IsTrue(RegexValidators::isValidSuchThatClRegex(str));
        }

        TEST_METHOD(TestRegex_SuchThatCl_Whitespace_Valid)
        {
            string str = "   such        that     Follows   (  1   ,   2   )   and    Parent    (   1   ,    2   )   ";
            Assert::IsTrue(RegexValidators::isValidSuchThatClRegex(str));
        }

    };
}
