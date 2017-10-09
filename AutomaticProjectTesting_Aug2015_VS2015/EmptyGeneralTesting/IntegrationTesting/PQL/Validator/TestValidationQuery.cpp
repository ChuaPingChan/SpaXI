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
        /**************************
        * Select Clause - BOOLEAN *
        **************************/
        TEST_METHOD(TestValidity_Query_SelectBoolean_ValidDeclaration_ExpectTrue_Valid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select BOOLEAN");
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_InvalidDeclaration_ExpectFalse_Invalid)
        {
            string query;
            query.append("statement s;");
            query.append("Select BOOLEAN");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_NoDeclaration_Expect_True_Valid)
        {
            string query;
            query.append("Select BOOLEAN");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectBoolean_SuchThat_Valid)
        {
            string query;
            query.append("if RayYan;");
            query.append("call AllGods;");
            query.append("Select BOOLEAN such that Parent*(RayYan, AllGods)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_BOOLEAN);
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(PARENTSTAR, IF, "RayYan", CALL, "AllGods");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        
        /*********************************
        * Select Clause - Single Synonym *
        *********************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_Valid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s");
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Select_Valid)
        {
            string query;
            query.append("stmt Select;");
            query.append("Select Select");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "Select");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_Modifies_Valid)
        {
            string query;
            query.append("assign Modifies;");
            query.append("Select Modifies");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "Modifies");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_KeywordAsSynonym_assign_Valid)
        {
            string query;
            query.append("assign assign;");
            query.append("Select assign");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "assign");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
        }


        /********************************************
        * Select Clause - Single Synonym - SuchThat *
        ********************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SingleSuchThat_Relation_Valid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("Select s such that Modifies(s, v)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", VARIABLE, "v");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SingleSuchThat_Whitespace_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("   Select    a    such that    Follows*      (   a   ,   w   )  ");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_Relation_BeforeAndAfter_AndKeyword_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2) and Parent(w, s2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENT, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }
        
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_AndKeyword_StickToPreviousRelation_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("while w;");
            query.append("Select s2 such that Follows(s1, s2)and Parent(w, s2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENT, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultipleSuchThat_SuchThat_Relation_SuchThat_Relation_And_Relation_SuchThat_Relation_Valid)
        {
            string query;
            query.append("stmt s1, s2, s3;");
            query.append("while w;");
            query.append("variable v, v2;");
            query.append("Select w such that Follows*(s1, s2) such that Parent*(w, s2) and Modifies(s1, v) such that Uses(w, v2) and Follows(s1, s3)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, WHILE, "w");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", VARIABLE, "v"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(USES, WHILE, "w", VARIABLE, "v2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s1", STMT, "s3"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        /*---------Extra miscellaneous such that test cases----------*/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Modifies_Procedure_Variable_Valid)
        {
            string query;
            query.append("procedure Charizard;");
            query.append("variable Ash;");
            query.append("Select Charizard such that Modifies(Charizard, Ash)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "Charizard");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Charizard", VARIABLE, "Ash");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Modifies_IdentWQ_Variable_Valid)
        {
            string query;
            query.append("variable Masterball;");
            query.append("Select Masterball such that Modifies(\"MewTwo\", Masterball)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, VARIABLE, "Masterball");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "\"MewTwo\"", VARIABLE, "Masterball");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_SingleSuchThat_Uses_IdentWQ_Variable_Valid)
        {
            string query;
            query.append("procedure Pokemon;");
            query.append("Select Pokemon such that Uses(\"Azelf\", \"Psychic\")");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "Pokemon");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(USES, IDENT_WITHQUOTES, "\"Azelf\"", IDENT_WITHQUOTES, "\"Psychic\"");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_SingleSuchThat_FollowsStar_Assign_While_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such that Follows*(a, w)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            SuchThatClause expectedStc = UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, ASSIGN, "a", WHILE, "w");
            SuchThatClause actualStc = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expectedStc, actualStc));
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
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, WHILE, "w", STMT, "s2"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Procedure_Calls_Procedure_Variable_And_Modifies_Procedure_Variable_Valid)
        {
            string query;
            query.append("procedure p;");
            query.append("procedure q;");
            query.append("variable v;");
            query.append("Select p such that Calls(p, q) and Modifies(p, v)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, PROCEDURE, "p");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedList;
            expectedList.push_back(UtilitySelection::makeSuchThatClause(CALLS, PROCEDURE, "p", PROCEDURE, "q"));
            expectedList.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "p", VARIABLE, "v"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedList, qt));
        }

        


        /*******************************************
        * Select Clause - Single Synonym - Pattern *
        *******************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_SinglePattern_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("variable v;");
            query.append("Select a pattern a(v, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            PatternClause expectedPc = UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_");
            PatternClause actualPc = UtilitySelection::getFirstPatternClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSamePatternClauseAssignWhileContent(expectedPc, actualPc));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Type_BeforeAndAfter_AndKeyword_Valid)
        {
            string query;
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _) and a2(_,_)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_AndKeyword_StickToPreviousType_Valid)
        {
            string query;
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _)and a2(_,_)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Pattern_AfterAndKeyword_Valid)
        {
            string query;
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select a2 pattern a1(v, _) and a2(_,_) pattern a1 (v, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, qt));
        }


        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_MultiPattern_Pattern_Assign_And_While_And_If_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("variable v;");
            query.append("while w;");
            query.append("if f;");
            query.append("Select a pattern a(v, _) and w(_,_) and f(v, _ , _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(If_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, qt));
        }

        /*---------Extra miscellaneous pattern test cases----------*/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Assign_Pattern_Assign_And_While_Valid)
        {
            string query;
            query.append("assign a;");
            query.append("variable v;");
            query.append("while w;");
            query.append("Select a pattern a(v, _) and w(_,_)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, ASSIGN, "a");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<PatternClause> expectedList;
            expectedList.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a", VARIABLE, "v", UNDERSCORE, "_"));
            expectedList.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedList, qt));
        }

        TEST_METHOD(TestValidity_Query_Pattern_If_AsFirstClause_Valid)
        {
            string query;
            query.append("call cl;");
            query.append("variable v;");
            query.append("if f;");
            query.append("Select cl pattern f (v, _, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "cl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListPc.push_back(UtilitySelection::makePatternClause(If_PATTERN, "f", VARIABLE, "v", UNDERSCORE, "_", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, qt));
        }

        /****************************************
        * Select Clause - Single Synonym - With *
        ****************************************/

        /********************************************************
        * Select Clause - Single Synonym - SuchThat and Pattern *
        ********************************************************/
        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_SuchThat_Parent_Pattern_Assign_And_Assign_SuchThat_Follows_And_Modifies_Pattern_Assign_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("assign a1, a2;");
            query.append("variable v;");
            query.append("Select s2 such that Parent(s1, s2) pattern a1(v, _) and a2(_,_) such that Follows(s2, s1) and Modifies(s1, \"x\") pattern a1 (v, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENT, STMT, "s1", STMT, "s2"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s2", STMT, "s1"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", IDENT_WITHQUOTES, "\"x\""));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, qt));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Stmt_Parent_Pattern_Assign_And_While_SuchThat_Follows_And_Modifies_Pattern_Valid)
        {
            string query;
            query.append("stmt s1, s2;");
            query.append("assign a1, a2;");
            query.append("while w1, w2;");
            query.append("variable v1, v2;");
            query.append("Select s2 such that Parent(s1, s2) pattern a1(v2, _) and w1(\"y\",_) such that Follows(s2, s1) and Modifies(s1, \"x\") pattern w2 (v1, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, STMT, "s2");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENT, STMT, "s1", STMT, "s2"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v2", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w1", IDENT_WITHQUOTES, "\"y\"", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWS, STMT, "s2", STMT, "s1"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s1", IDENT_WITHQUOTES, "\"x\""));
            expectedListPc.push_back(UtilitySelection::makePatternClause(WHILE_PATTERN, "w2", VARIABLE, "v1", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, qt));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, qt));
        }

        TEST_METHOD(TestValidity_Query_SelectSingleSynonym_Call_Pattern_Assign_SuchThat_FollowsStar_And_ParentStar_SuchThat_Modifies_Pattern_Assign_Pattern_Assign_Valid)
        {
            string query;
            query.append("call cl;");
            query.append("stmt s1, s2, s3;");
            query.append("variable v;");
            query.append("assign a1, a2;");
            query.append("Select cl pattern a1(v, _) such that Follows*(s1, s2) and Parent*(s2, s3) such that Modifies(1, v) pattern a2(_, _) pattern a2(v, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsTrue(validator.isValidQuery(query));
            SelectClause expected = UtilitySelection::makeSelectClause(SELECT_SINGLE, CALL, "cl");
            Assert::IsTrue(UtilitySelection::isSameSelectClauseContent(expected, qt.getSelectClause()));
            vector<SuchThatClause> expectedListStc;
            vector<PatternClause> expectedListPc;
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a1", VARIABLE, "v", UNDERSCORE, "_"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(FOLLOWSSTAR, STMT, "s1", STMT, "s2"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(PARENTSTAR, STMT, "s2", STMT, "s3"));
            expectedListStc.push_back(UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", VARIABLE, "v"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", UNDERSCORE, "_", UNDERSCORE, "_"));
            expectedListPc.push_back(UtilitySelection::makePatternClause(ASSSIGN_PATTERN, "a2", VARIABLE, "v", UNDERSCORE, "_"));
            Assert::IsTrue(UtilitySelection::AreSameSuchThatClausesContentAsInTree(expectedListStc, qt));
            Assert::IsTrue(UtilitySelection::areSamePatternClausesContentAsInTree(expectedListPc, qt));
        }


        /*****************************************************
        * Select Clause - Single Synonym - SuchThat and With *
        *****************************************************/

        /****************************************************
        * Select Clause - Single Synonym - Pattern and With *
        ****************************************************/

        /*****************************************************************
        * Select Clause - Single Synonym - SuchThat and Pattern and With *
        *****************************************************************/

        /***********************************
        * Select Clause - Tuple - SuchThat *
        ***********************************/
        

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
            query.append("Select a such that Follows    *      (a,w)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_WhitespaceWithinKeyword_Invalid)
        {
            string query;
            query.append("assign a;");
            query.append("while w;");
            query.append("Select a such            that Follows(a,w)");
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

        TEST_METHOD(TestValidity_Query_SuchThat_Follows_Int_Int_SecondArg_GreaterThan_FirstArg_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s such that Follows(15, 2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Parent_Int_Int_SecondArg_GreaterThan_FirstArg_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s such that Parent(15, 2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_KeywordsBackToBack_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("Select s such thatParent(1, 2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Relation_And_Pattern_Type_And_SuchThat_Relation_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("while w;");
            query.append("assign a1, a2;");
            query.append("Select s such that Modifies(1, v) and pattern a1(_, _) and such that Parent(w, a2)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Modifies_And_Assign_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s such that Modifies(1, v) and a(_, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_Pattern_Assign_And_Modifies_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s pattern a(_, _) and Modifies(1, v)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }

        TEST_METHOD(TestValidity_Query_SuchThat_Assign_Invalid)
        {
            string query;
            query.append("stmt s;");
            query.append("variable v;");
            query.append("assign a;");
            query.append("Select s such that a(v, _)");
            QueryTree qt;
            QueryValidator validator = QueryValidator(&qt);
            Assert::IsFalse(validator.isValidQuery(query));
        }
    };
}