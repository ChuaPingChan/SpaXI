#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryValidatorOld.h"
#include "..\SPA\PQL\QueryValidatorFriend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestQueryValidator)
    {
    public:
        
        /******************
        * Tokenizer Tests *
        ******************/
        TEST_METHOD(TestToknenizer_Split_Equality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a;select a;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreEqual((std::string) "assign a", splitted.at(0));
            Assert::AreEqual((std::string) "select a", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_SplitWithSpaces_Equality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a     ; select a     ;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreEqual((std::string) "assign a     ", splitted.at(0));
            Assert::AreEqual((std::string) " select a     ", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_SplitWithSpaces_Inequality)
        {
            QueryValidatorFriend qvf;
            string str = "assign a     ; select a     ;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreNotEqual((std::string) "assign a", splitted.at(0));
            Assert::AreNotEqual((std::string) " select a", splitted.at(1));
        }

        TEST_METHOD(TestToknenizer_WithNewDeclarationAtStart_Inequality)
        {
            QueryValidatorFriend qvf;
            string str = "while w;assign a;select a;";
            vector<string> splitted = qvf.tokenize(str);
            Assert::AreNotEqual((std::string) "assign a", splitted.at(0));
            Assert::AreNotEqual((std::string) " select a", splitted.at(1));
        }


        /********************
        * Remove all spaces *
        ********************/
        TEST_METHOD(TestRemoveAllSpaces)
        {
            QueryValidatorFriend qvf;
            string str = " a  b    c  ";
            Assert::IsTrue(qvf.removeAllSpaces(str) == "abc");
        }


        /******************
        * Substring Tests *
        ******************/
        TEST_METHOD(TestSubstringBetween_UniqueCharDelims)
        {
            QueryValidatorFriend qvf;
            string str = "abcdefghijklmnop#$%123456789";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "g", "5") == "hijklmnop#$%1234");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "c", "7") == "hijklmnop#$%1234");
        }

        /*TEST_METHOD(TestSubstringBetweenSameCharDelims)
        {
        QueryValidatorFriend qvf;
        string str = "TestBetweenSameCharDelims";
        Assert::IsTrue(qvf.getBetweenTwoStrings(str, "e", "e") == "stBetweenSameCharD");
        Assert::IsFalse(qvf.getBetweenTwoStrings(str, "e", "e") == "stBetwe");
        }*/

        /*TEST_METHOD(TestSubstringBetweenWhiteSpaceDelims)
        {
        QueryValidatorFriend qvf;
        string str = "Test between white space delims";
        Assert::IsTrue(qvf.getBetweenTwoStrings(str, " ", " ") == "between");
        Assert::IsFalse(qvf.getBetweenTwoStrings(str, " ", " ") == "white space");
        }*/

        TEST_METHOD(TestSubstringBetweenDelims_ExtractUsesArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Uses(a,b)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "a");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "b");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "(", ",") == "(a");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ")") == "b)");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractModifiesArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Modifes(abc,def)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "abc");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "def");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, "(", ",") == "(awf");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "31") == "awfwf");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractFollowsArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Follows(a,b)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "a");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "b");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ",") == "qeeq");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractFollowsStarArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Follows*(123,456)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "123");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "456");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "rwr") == "3121");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractParentArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Parent(abc123,def)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "abc123");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "def");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "\"") == "qeeq");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractParentStarArgs)
        {
            QueryValidatorFriend qvf;
            string str = "Parent*(1,2)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "Parent", "(") == "*");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "Parent*(", ",") == "1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "2");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", "2") == ",");
        }

        TEST_METHOD(TestSubstringBetweenDelims_ExtractPatternArgs)
        {
            QueryValidatorFriend qvf;
            string str = "patternarg1(arg2,arg3)";
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "pattern", "(") == "arg1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "(", ",") == "arg2");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, ",", ")") == "arg3");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "ern", "(") == "arg1");
            Assert::IsTrue(qvf.getBetweenTwoStrings(str, "arg2", "arg3") == ",");
            Assert::IsFalse(qvf.getBetweenTwoStrings(str, ",", ")") == "arg2");
        }

        /******************************
        * Entire query Validity Tests *
        ******************************/
        TEST_METHOD(TestQueryValidity)
        {
            QueryValidatorOld qv;
            string query = "assign a; variable v; Select v";

            Assert::IsTrue(qv.isValidQuery(query));
        }


    };
}
