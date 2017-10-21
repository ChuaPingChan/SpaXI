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
            string str = "stmt s;";
            Assert::IsTrue(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_Whitespaces_Valid)
        {
            string str = "    stmt    s     ;   ";
            Assert::IsTrue(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_BadArrangement_Invalid)
        {
            string str = "  s   stmt       ;   ";
            Assert::IsFalse(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_SingleSynonym_RedundantComma_Invalid)
        {
            string str = " stmt s, ;";
            Assert::IsFalse(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_NoSynonym_Invalid)
        {
            string str = "    assign     ;   ";
            Assert::IsFalse(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_Declaration_NoEntity_Invalid)
        {
            string str = "  synonym    ;   ";
            Assert::IsFalse(RegexValidators::isValidDeclarationRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_MultipleSynonym_MissingComma_Invalid)
        {
            string str = "stmt s1 s2 s3, s4, s5;";
            Assert::IsFalse(RegexValidators::isValidDeclarationOverallRegex(str));
        }


        /****************************
        * Declaration Overall Regex *
        ****************************/
        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_SingleSynonym_Valid)
        {
            string str = "stmt s;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_MultipleSynonym_CommaStickBack_Valid)
        {
            string str = "stmt s1, s2, s3, s4, s5;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_MultipleSynonym_CommaStickFront_Valid)
        {
            string str = "stmt s1 ,s2 ,s3 ,s4 ,s5;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_SingleEntity_MultipleSynonym_Whitespace_Valid)
        {
            string str = "  stmt   s1   ,  s2   ,   s3   ,   s4  ,   s5;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_MultipleEntity_SingleSynonym_Valid)
        {
            string str = "stmt s; assign a; procedure p;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_MultipleEntity_MultipleSynonym_CommaStickBack_Valid)
        {
            string str = "stmt s1, s2, s3, s4, s5; assign a1, a2, a3, a4, a5; while w1, w2;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_MultipleEntity_MultipleSynonym_CommaStickFront_Valid)
        {
            string str = "stmt s1 ,s2 ,s3 ,s4 ,s5 ;assign a1 ,a2 ,a3 ,a4 ,a5 ;while w1 ,w2 ;";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        TEST_METHOD(TestRegex_DeclarationOverall_MultipleEntity_MultipleSynonym_Whitespace_Valid)
        {
            string str = "  stmt   s1   ,  s2   ,   s3   ,   s4  ,   s5  ;  assign   a1   ,   a2   , a3   , a4   , a5 ; while  w1 ,  w2  ; ";
            Assert::IsTrue(RegexValidators::isValidDeclarationOverallRegex(str));
        }

        
    };
}