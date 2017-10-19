#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\ResultFormatter\ResultFormatter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexResultFormatter)
    {
    public:

        /************************
        * Return false result *
        ************************/

        TEST_METHOD(TestRegex_EmptyDeclaration_FalseResult)
        {
            ResultFormatter rf;
            string query = ";Select BOOLEAN";
            list<string> expectedResult = { "false" };
            Assert::IsTrue(rf.handleInvalidQuery(query) == expectedResult);
        }

        TEST_METHOD(TestRegex_InvalidDeclaration_FalseResult)
        {
            ResultFormatter rf;
            string query = "stmt 12739813279; Select BOOLEAN";
            list<string> expectedResult = { "false" };
            Assert::IsTrue(rf.handleInvalidQuery(query) == expectedResult);
        }

        TEST_METHOD(TestRegex_InvalidQueryRelation_FalseResult)
        {
            ResultFormatter rf;
            string query = "stmt s;Select BOOLEAN such that Bag(1, 2)";
            list<string> expectedResult = { "false" };
            Assert::IsTrue(rf.handleInvalidQuery(query) == expectedResult);
        }

        TEST_METHOD(TestRegex_InvalidDeclarationWithMultipleSemiColons_FalseResult)
        {
            ResultFormatter rf;
            string query = "stmt s;;;;;;;;;;; Select BOOLEAN";
            list<string> expectedResult = { "false" };
            Assert::IsTrue(rf.handleInvalidQuery(query) == expectedResult);
        }

        TEST_METHOD(TestRegex_QueryWithInvalidStart_EmptyResult)
        {
            ResultFormatter rf;
            string query = "stmt s;Random Select BOOLEAN";
            Assert::IsTrue(rf.handleInvalidQuery(query).empty());
        }

        TEST_METHOD(TestRegex_ValidDeclarationFollowedByInvalidDeclaration_EmptyResult)
        {
            ResultFormatter rf;
            string query = "stmt s; 3791237937897192# Select BOOLEAN";
            Assert::IsTrue(rf.handleInvalidQuery(query).empty());
        }
    };
}
