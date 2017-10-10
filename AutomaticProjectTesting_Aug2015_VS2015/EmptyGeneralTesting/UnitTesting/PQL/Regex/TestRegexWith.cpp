#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexWith)
    {
    public:

        /*****************
        * Ref Regex Test *
        *****************/
        TEST_METHOD(TestRegex_Ref_IdentWithQuotes_Valid)
        {
            string str = "\"validIdent\"";
            Assert::IsTrue(RegexValidators::isValidRefRegex(str));
        }

        TEST_METHOD(TestRegex_Ref_Int_Valid)
        {
            string str = "123456";
            Assert::IsTrue(RegexValidators::isValidRefRegex(str));
        }

        TEST_METHOD(TestRegex_Ref_AttrRef_Valid)
        {
            string str = "synonym.procName";
            Assert::IsTrue(RegexValidators::isValidRefRegex(str));
        }

        TEST_METHOD(TestRegex_Ref_AttrRef_Synonym_Valid)
        {
            string str = "validSynonym";
            Assert::IsTrue(RegexValidators::isValidRefRegex(str));
        }

        TEST_METHOD(TestRegex_Ref_AttrRef_Whitespace_Valid)
        {
            string str = "   synonym.procName    ";
            Assert::IsTrue(RegexValidators::isValidRefRegex(str));
        }

        TEST_METHOD(TestRegex_Ref_AttrRef_Wrong_Invalid)
        {
            string str = "synonym.count";
            Assert::IsFalse(RegexValidators::isValidRefRegex(str));
        }


        /**************************
        * Attr Compare Regex Test *
        **************************/
        TEST_METHOD(TestRegex_AttrCompare_ProcName_Ident_Valid)
        {
            string str = "p.procName=\"Pikachu\"";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Ident_ProcName_Valid)
        {
            string str = "\"Pikachu\"=p.procName";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_ProcName_ProcName_Valid)
        {
            string str = "p1.procName=p2.procName";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_VarName_Ident_Valid)
        {
            string str = "v.varName=\"Raichu\"";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Ident_VarName_Valid)
        {
            string str = "\"Raichu\"=v.varName";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_VarName_VarName_Valid)
        {
            string str = "v1.varName=v2.varName";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Value_Integer_Valid)
        {
            string str = "c.value=12345";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Integer_Value_Valid)
        {
            string str = "12345=c.value";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Value_Value_Valid)
        {
            string str = "c1.value=v2.value";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_StmtNum_Int_Valid)
        {
            string str = "s.stmt#=12345";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_StmtNum_stmtNum_Valid)
        {
            string str = "s1.stmt#=s2.stmt#";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_ProgLine_StmtNum_Valid)
        {
            string str = "proglineP = s2.stmt#";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_Whitespace_Valid)
        {
            string str = "   s1.stmt#   =   s2.stmt#   ";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        /**********************************************************
        * Syntactically valid - does not imply semantically valid *
        **********************************************************/
        TEST_METHOD(TestRegex_AttrCompare_ProcName_Integer_Valid)
        {
            string str = "p.procName=12345";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_FirstArg_NotArrtRef_Invalid)
        {
            string str = "ab = 123";
            Assert::IsTrue(RegexValidators::isValidAttrCompareRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCompare_IllegalWhitespace_Invalid)
        {
            string str = "   s1   .   stmt#   =   s2   .   stmt#   ";
            Assert::IsFalse(RegexValidators::isValidAttrCompareRegex(str));
        }


        /***********************
        * Attr Cond Regex Test *
        ***********************/
        TEST_METHOD(TestRegex_AttrCond_ProcName_Ident_And_ProcName_Ident_Valid)
        {
            string str = "p1.procName=\"pikachu\" and p2.procName=\"Charizard\"";
            Assert::IsTrue(RegexValidators::isValidAttrCondRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCond_ProcName_Ident_And_ProcName_Ident_And_StmtNum_Int_Valid)
        {
            string str = "p1.procName=\"pikachu\" and p2.procName=\"Charizard\" and s.stmt#=12345";
            Assert::IsTrue(RegexValidators::isValidAttrCondRegex(str));
        }

        TEST_METHOD(TestRegex_AttrCond_ProcName_Ident_And_ProcName_Ident_Whitespace_Valid)
        {
            string str = "    p1.procName=    \"pikachu\"      and    p2.procName   =   \"Charizard\" ";
            Assert::IsTrue(RegexValidators::isValidAttrCondRegex(str));
        }
    };
}
