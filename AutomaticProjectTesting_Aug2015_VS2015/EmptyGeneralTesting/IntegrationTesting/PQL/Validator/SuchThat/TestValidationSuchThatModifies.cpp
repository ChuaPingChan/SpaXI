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
    TEST_CLASS(TestValidationSuchThat_Modifies)
    {
    public:
        string str;
        QueryTree *qtPtr;
        SuchThatHandler stHandler = SuchThatHandler(qtPtr);

        TEST_METHOD_INITIALIZE(Test_Initialisation)
        {
            qtPtr = new QueryTree;
            stHandler = SuchThatHandler(qtPtr);
        }

        TEST_METHOD_CLEANUP(Test_Cleanup)
        {
            delete qtPtr;
            qtPtr = NULL;
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Int_IdentWithQuotes_Valid)
        {
            str = "Modifies(1, \"x\")";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", IDENT_WITHQUOTES, "x");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Int_Underscore_Valid)
        {
            str = "Modifies(1, _)";
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Int_Variable_Valid)
        {
            str = "Modifies(1, v)";
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, INTEGER, "1", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Synonym_IdentWithQuotes_Valid)
        {
            str = "Modifies(a, \"x\")";
            qtPtr->insertSynonym(ASSIGN, "a");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, ASSIGN, "a", IDENT_WITHQUOTES, "x");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Synonym_Underscore_Valid)
        {
            str = "Modifies(s, _)";
            qtPtr->insertSynonym(STMT, "s");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, STMT, "s", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Synonym_Variable_Valid)
        {
            str = "Modifies(w, v)";
            qtPtr->insertSynonym(WHILE, "w");
            qtPtr->insertSynonym(VARIABLE, "v");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, WHILE, "w", VARIABLE, "v");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Synonym_IdentWithQuotes_Similar_Valid)
        {
            str = "Modifies(Pikachu, \"Pikachu\")";
            qtPtr->insertSynonym(PROCEDURE, "Pikachu");
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Pikachu", IDENT_WITHQUOTES, "Pikachu");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_IdentWithQuotes_IdentWithQuotes_Diff_Valid)
        {
            str = "Modifies(\"Pikachu\", \"pokeball\")";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"pokeball\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "Pikachu", IDENT_WITHQUOTES, "pokeball");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_IdentWithQuotes_IdentWithQuotes_Same_Valid)
        {
            str = "Modifies(\"Pikachu\", \"Pikachu\")";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "Pikachu", IDENT_WITHQUOTES, "Pikachu");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_IdentWithQuotes_Underscore_Valid)
        {
            str = "Modifies(\"Pikachu\", _)";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qtPtr->insertSynonym(UNDERSCORE, "_");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "Pikachu", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_IdentWithQuotes_Variable_Valid)
        {
            str = "Modifies(\"Pikachu\", thunderstone)";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qtPtr->insertSynonym(VARIABLE, "thunderstone");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "Pikachu", VARIABLE, "thunderstone");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_IdentWithQuotes_Variable_Similar_Valid)
        {
            str = "Modifies(\"Pikachu\", Pikachu)";
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"Pikachu\"");
            qtPtr->insertSynonym(VARIABLE, "Pikachu");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, IDENT_WITHQUOTES, "Pikachu", VARIABLE, "Pikachu");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Procedure_IdentWithQuotes_Valid)
        {
            str = "Modifies(Blastoise, \"pokeball\")";
            qtPtr->insertSynonym(PROCEDURE, "Blastoise");
            qtPtr->insertSynonym(IDENT_WITHQUOTES, "\"pokeball\"");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", IDENT_WITHQUOTES, "pokeball");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Procedure_Underscore_Valid)
        {
            str = "Modifies(Blastoise, _ )";
            qtPtr->insertSynonym(PROCEDURE, "Blastoise");
            qtPtr->insertSynonym(UNDERSCORE, "_");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", UNDERSCORE, "_");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }

        TEST_METHOD(TestValidity_SuchThat_Modifies_Procedure_Variable_Valid)
        {
            str = "Modifies(Blastoise, hydroCannon)";
            qtPtr->insertSynonym(PROCEDURE, "Blastoise");
            qtPtr->insertSynonym(VARIABLE, "hydroCannon");
            Assert::IsTrue(stHandler.isValidSuchThat(str));
            SuchThatClause expected = UtilitySelection::makeSuchThatClause(MODIFIES, PROCEDURE, "Blastoise", VARIABLE, "hydroCannon");
            SuchThatClause actual = UtilitySelection::getFirstSuchThatClauseFromTree(*qtPtr);
            Assert::IsTrue(UtilitySelection::isSameSuchThatClauseContent(expected, actual));
        }
    };
}
