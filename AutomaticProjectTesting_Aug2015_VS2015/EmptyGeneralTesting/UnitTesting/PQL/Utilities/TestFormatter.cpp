#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Utilities\Formatter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestFormatter)
    {
    public:
        TEST_METHOD(TestFormatter_RemovesAllQuotes_Valid)
        {
            string orgStr = "\"Good Morning!\"";
            string res = Formatter::removeAllQuotes(orgStr);
            Assert::IsTrue(res == "Good Morning!");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_OneOcurrence_Valid)
        {
            string orgStr = "Modifies(1,v)";
            string res = Formatter::getBetweenTwoDelims(orgStr, "(", ",");
            Assert::IsTrue(res == "1");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_MultipleOccurrence_ExpectResultFromFirstOccurrence_Valid)
        {
            string orgStr = "Modifies(1,v) and Uses(2,y)";
            string res = Formatter::getBetweenTwoDelims(orgStr, "(", ",");
            Assert::IsTrue(res == "1");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_OneOccurence_Valid)
        {
            string orgStr = "if(a,b,c)";
            string res = Formatter::getBetweenTwoDelims(orgStr, ",", ",");
            Assert::IsTrue(res == "b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_MultipleOccurrence_ExpectResultFromFirstOccurrence_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoDelims(orgStr, ",", ",");
            Assert::IsTrue(res == "b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_From_Start_To_Delim_Valid)
        {
            string orgStr = "c.value=a.stmt#";
            string res = Formatter::getBetweenTwoDelims(orgStr, "", "=");
            Assert::IsTrue(res == "c.value");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_MultipleOccurrence_ExpectResultFromSecondOccurrence_Valid)
        {
            string orgStr = "Modifies(1,v) and Uses(2,y)";
            string res = Formatter::getBetweenTwoDelims(orgStr, "(", 2, ",", 1);
            Assert::IsTrue(res == "2");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_MultipleOccurrence_ExpectResultFromSecondOccurrence_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoDelims(orgStr, ",", 2, ",", 1);
            Assert::IsTrue(res == "c");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_UniqueDelims_OneOcurrence_Valid)
        {
            string orgStr = "Good day! Thank you for reviewing our code! :)";
            string res = Formatter::getBetweenTwoDelims(orgStr, "Thank ", " reviewing");
            Assert::IsTrue(res == "you for");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_UniqueDelims_MultipleOccurrence_FirstOcc_SecondOccAfterFirst_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoDelims(orgStr, "(", 1, ",", 2);
            Assert::IsTrue(res == "a,b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_SameDelims_MultipleOccurrence_FirstOcc_ThirdOccAfterFirst_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoDelims(orgStr, ",", 1, ",", 3);
            Assert::IsTrue(res == "b,c,d");
        }

        TEST_METHOD(TestFormatter_GetStringBeforeDelim_SingleCharDelim_Valid)
        {
            string orgStr = "c.value=s.stmt#";
            string res = Formatter::getStringBeforeDelim(orgStr, "=");
            Assert::IsTrue(res == "c.value");
        }

        TEST_METHOD(TestFormatter_GetStringBeforeDelim_MultiCharDelim_Valid)
        {
            string orgStr = "Thank you very much";
            string res = Formatter::getStringBeforeDelim(orgStr, " you");
            Assert::IsTrue(res == "Thank");
        }

        TEST_METHOD(TestFormatter_GetStringAfterDelim_SingleCharDelim_Valid)
        {
            string orgStr = "c.value=s.stmt#";
            string res = Formatter::getStringAfterDelim(orgStr, "=");
            Assert::IsTrue(res == "s.stmt#");
        }

        TEST_METHOD(TestFormatter_GetStringAfterDelim_MultiCharDelim_Valid)
        {
            string orgStr = "Thank you very much";
            string res = Formatter::getStringAfterDelim(orgStr, "you ");
            Assert::IsTrue(res == "very much");
        }

    };
}