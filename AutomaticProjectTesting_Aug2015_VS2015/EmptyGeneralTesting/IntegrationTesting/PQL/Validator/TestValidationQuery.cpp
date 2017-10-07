#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\Entity.h"
#include "..\SPA\PQL\Validator\QueryValidator.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationQuery)
    {
    public:
        /****************
        * Valid Queries *
        ****************/

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_Valid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s");
            QueryTree qt;
            qt.insertVariable(STMT, "s");
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Select_Valid)
        {
            string query;
            query.append("stmt Select;");
            query.append("Select Select");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Modifies_Valid)
        {
            string query;
            query.append("assign Modifies;");
            query.append("Select Modifies");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_assign_Valid)
        {
            string query;
            query.append("assign assign;");
            query.append("Select assign");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_SingleSuchThat_Modifies_Valid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("Select s such that Modifies(s, v)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_SingleSuchThat_FollowsStar_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such that Follows*(a, w)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_SingleSuchThat_FollowsStar_Whitespace_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("   Select    a    such    that    Follows*      (   a   ,   w   )  ");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }



        /******************
        * Invalid Queries *
        ******************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_NonDeclaredSynonym_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select a");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_Selection_Before_Declaration_Invalid)
        {
            string query;
            query.append("Select s such that Modifies(s, v);");
            query.append("stmt s;");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_SingleSuchThat_Modifies_SecondArgInt_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s such that Modifies(s, 12)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_FollowsStar_Whitespace_StarNotConnectedToKeyword_Invalid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("   Select    a    such    that    Follows    *      (   a   ,   w   )  ");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }
    };
}