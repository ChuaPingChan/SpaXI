#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\QueryTree.h"
#include "..\SPA\Entity.h"
#include "..\SPA\PQL\Relationship.h"
#include "..\SPA\PQL\Validator\Selection\SuchThat\SuchThatHandler.h"
#include "..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\Utility\UtilitySelection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestValidationSuchThatModifies)
    {
    public:
        TEST_METHOD(TestValidity_SuchThatModifies_Int_IdentWithQuotes_Valid)
        {
            string str = "Modifies(1, \"x\")";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", IDENT_WITHQUOTES, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Underscore_Valid)
        {
            string str = "Modifies(1, _)";
            QueryTree qt;
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Int_Variable_Valid)
        {
            string str = "Modifies(1, v)";
            QueryTree qt;
            qt.insertSynonym(VARIABLE, "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_IdentWithQuotes_Valid)
        {
            string str = "Modifies(a, \"x\")";
            QueryTree qt;
            qt.insertSynonym(ASSIGN, "a");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, ASSIGN, "a", IDENT_WITHQUOTES, "\"x\"");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Underscore_Valid)
        {
            string str = "Modifies(s, _)";
            QueryTree qt;
            qt.insertSynonym(STMT, "s");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Synonym_Variable_Valid)
        {
            string str = "Modifies(w, v)";
            QueryTree qt;
            qt.insertSynonym(WHILE, "w");
            qt.insertSynonym(VARIABLE, "v");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, WHILE, "w", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_IdentWithQuotes_IdentWithQuotes_Valid)
        {
            string str = "Modifies(\"Pikachu\", \"pokeball\")";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qt.insertSynonym(IDENT_WITHQUOTES, "\"pokeball\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "\"Pikachu\"", IDENT_WITHQUOTES, "\"pokeball\"");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_IdentWithQuotes_Underscore_Valid)
        {
            string str = "Modifies(\"Pikachu\", _)";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qt.insertSynonym(UNDERSCORE, "_");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "\"Pikachu\"", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_IdentWithQuotes_Variable_Valid)
        {
            string str = "Modifies(\"Pikachu\", thunderstone)";
            QueryTree qt;
            qt.insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qt.insertSynonym(VARIABLE, "thunderstone");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "\"Pikachu\"", VARIABLE, "thunderstone");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Procedure_IdentWithQuotes_Valid)
        {
            string str = "Modifies(Blastoise, \"pokeball\")";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "Blastoise");
            qt.insertSynonym(IDENT_WITHQUOTES, "\"pokeball\"");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", IDENT_WITHQUOTES, "\"pokeball\"");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Procedure_Underscore_Valid)
        {
            string str = "Modifies(Blastoise, _ )";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "Blastoise");
            qt.insertSynonym(UNDERSCORE, "_");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThatModifies_Procedure_Variable_Valid)
        {
            string str = "Modifies(Blastoise, hydroCannon)";
            QueryTree qt;
            qt.insertSynonym(PROCEDURE, "Blastoise");
            qt.insertSynonym(VARIABLE, "hydroCannon");
            SuchThatHandler stHandler = SuchThatHandler(&qt);
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", VARIABLE, "hydroCannon");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(qt);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }
    };
}
