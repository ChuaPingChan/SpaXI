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
            qt.insertSynonym(STMT, "s");
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

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_MultipleSuchThat_Follows_And_Parent_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2) and Parent(w, s2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENT, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_MultipleSuchThat_FollowsStar_SuchThat_ParentStar_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows*(s1, s2) such that Parent*(w, s2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_While_MultipleSuchThat_FollowsStar_SuchThat_ParentStar_And_Modifies_SuchThat_Uses_And_Follows_Valid)
        {
            string query;
            query.append("stmt s1, s2, s3;");
            query.append("while w;");
            query.append("variable v, v2;");
            query.append("Select w such that Follows*(s1, s2) such that Parent*(w, s2) and Modifies(s1, v) such that Uses(w, v2) and Follows(s1, s3)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", VARIABLE, "v"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(USES, WHILE, "w", VARIABLE, "v2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s3"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
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

        TEST_METHOD(TestValidity_Query_SuchThat_Keyword_And_Missing_Invalid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2) Parent(w, s2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }
    };
}