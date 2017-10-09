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
        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_OneOcurrence_Valid)
        {
            string orgStr = "Modifies(1,v)";
            string res = Formatter::getBetweenTwoStrings(orgStr, "(", ",");
            Assert::IsTrue(res == "1");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_MultipleOccurrence_ExpectResultFromFirstOccurrence_Valid)
        {
            string orgStr = "Modifies(1,v) and Uses(2,y)";
            string res = Formatter::getBetweenTwoStrings(orgStr, "(", ",");
            Assert::IsTrue(res == "1");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_OneOccurence_Valid)
        {
            string orgStr = "if(a,b,c)";
            string res = Formatter::getBetweenTwoStrings(orgStr, ",", ",");
            Assert::IsTrue(res == "b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_MultipleOccurrence_ExpectResultFromFirstOccurrence_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoStrings(orgStr, ",", ",");
            Assert::IsTrue(res == "b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_UniqueDelims_MultipleOccurrence_ExpectResultFromSecondOccurrence_Valid)
        {
            string orgStr = "Modifies(1,v) and Uses(2,y)";
            string res = Formatter::getBetweenTwoStrings(orgStr, "(", 2, ",", 1);
            Assert::IsTrue(res == "2");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_SingleCharDelim_SameDelims_MultipleOccurrence_ExpectResultFromSecondOccurrence_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoStrings(orgStr, ",", 2, ",", 1);
            Assert::IsTrue(res == "c");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_UniqueDelims_OneOcurrence_Valid)
        {
            string orgStr = "Good day! Thank you for reviewing our code! :)";
            string res = Formatter::getBetweenTwoStrings(orgStr, "Thank ", " reviewing");
            Assert::IsTrue(res == "you for");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_UniqueDelims_MultipleOccurrence_FirstOcc_SecondOccAfterFirst_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoStrings(orgStr, "(", 1, ",", 2);
            Assert::IsTrue(res == "a,b");
        }

        TEST_METHOD(TestFormatter_GetBetweenTwoString_MultiCharDelim_SameDelims_MultipleOccurrence_FirstOcc_ThirdOccAfterFirst_Valid)
        {
            string orgStr = "if(a,b,c,d,e,f,g)";
            string res = Formatter::getBetweenTwoStrings(orgStr, ",", 1, ",", 3);
            Assert::IsTrue(res == "b,c,d");
        }
    };
}