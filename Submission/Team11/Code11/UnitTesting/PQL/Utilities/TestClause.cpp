#include "CppUnitTest.h"
#include <string>
#include <queue>
#include <memory>

#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/Utilities/Clause.h"
#include "../SPA/PQL/Utilities/SuchThatClause.h"
#include "../SPA/PQL/Utilities/PatternClause.h"
#include "../SPA/PQL/Utilities/WithClause.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClause)
    {
    public:

        TEST_METHOD(TestSelectClauseGetSharedPtr_selectTuple) {
            SelectClause select_tuple_a1_v1 = SelectClause(SelectionType::SELECT_TUPLE,
                vector<Entity>{Entity::ASSIGN, Entity::VARIABLE},
                vector<string>{"a1", "v1"});

            SelectClausePtr scPtr;
            scPtr = select_tuple_a1_v1.getSharedPtr();

            // Checks if it can be retrieved properly.
            SelectClause retrievedClause = *scPtr;
            Assert::IsTrue(retrievedClause.getSelectionType() == SelectionType::SELECT_TUPLE);
            Assert::IsTrue(retrievedClause.getTupleArgTypes() == vector<Entity>{Entity::ASSIGN, Entity::VARIABLE});
            Assert::IsTrue(retrievedClause.getTupleArgs() == vector<string>{"a1", "v1"});
        }

        TEST_METHOD(TestSuchThatClauseGetSharedPtr) {
            SuchThatClause uses_a1_v1 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            SuchThatClausePtr stcPtr;
            stcPtr = uses_a1_v1.getSharedPtr();

            // Checks if it can be retrieved properly.
            SuchThatClause retrievedClause = *stcPtr;
            Assert::IsTrue(retrievedClause.getArgOne() == "a1");
            Assert::IsTrue(retrievedClause.getArgTwo() == "v1");
            Assert::IsTrue(retrievedClause.getArgOneType() == Entity::ASSIGN);
            Assert::IsTrue(retrievedClause.getArgTwoType() == Entity::VARIABLE);
            Assert::IsTrue(retrievedClause.getRel() == Relationship::USES);
        }

        TEST_METHOD(TestPatternClauseGetSharedPtr) {
            PatternClause if_w = PatternClause(PatternType::IF_PATTERN, "w",
                Entity::UNDERSCORE, "_", Entity::UNDERSCORE, "_");

            PatternClausePtr pcPtr;
            pcPtr = if_w.getSharedPtr();

            // Check if everything can be retrieved properly.
            PatternClause retrievedClause = *pcPtr;
            Assert::IsTrue(retrievedClause.getPatternType() == PatternType::IF_PATTERN);
            Assert::IsTrue(retrievedClause.getPatternSynonym() == "w");
            Assert::IsTrue(retrievedClause.getArgOneType() == Entity::UNDERSCORE);
            Assert::IsTrue(retrievedClause.getArgOne() == "_" );
        }

        TEST_METHOD(TestSynonymInitialization_TestGetSynonyms) {
            list<string> actualSynonyms;
            list<string> expectedSynonyms;

            SuchThatClause uses_a1_v1 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            actualSynonyms = uses_a1_v1.getSynonyms();
            expectedSynonyms = list<string>{ "a1", "v1" };

            actualSynonyms.sort();
            expectedSynonyms.sort();
            Assert::IsTrue(actualSynonyms == expectedSynonyms);
        }

        TEST_METHOD(TestGetClauseType_suchThatClause_success) {

            SuchThatClause uses_a1_v1 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            queue<Clause> clauseQueue;
            clauseQueue.push(uses_a1_v1);

            Clause clause = clauseQueue.front();

            Assert::IsTrue(clause.getClauseType() == Clause::ClauseType::SUCH_THAT);
            Assert::IsFalse(clause.getClauseType() == Clause::ClauseType::SELECT);
            Assert::IsFalse(clause.getClauseType() == Clause::ClauseType::PATTERN);
            Assert::IsFalse(clause.getClauseType() == Clause::ClauseType::WITH);
        }

        TEST_METHOD(TestRevertToActualClauseType_staticCast) {
            list<string> actualSynonyms;
            list<string> expectedSynonyms;

            // Create a sample "such that" clause
            SuchThatClause* uses_a1_v1 = new SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            // Put the sample clause in a queue of the parent type, then take it out and cast back
            queue<Clause*> clauseQueue;
            clauseQueue.push(uses_a1_v1);

            Clause* clausePtr = clauseQueue.front();

            SuchThatClause* clauseReverted = (SuchThatClause*)clausePtr;
            Assert::IsTrue(clauseReverted != NULL);

            // Check if variables are still the same
            actualSynonyms = clauseReverted->getSynonyms();
            expectedSynonyms = list<string>{ "a1", "v1" };
            actualSynonyms.sort();
            expectedSynonyms.sort();
            Assert::IsTrue(actualSynonyms == expectedSynonyms);

            // Test retrieving first argument
            string argOne = clauseReverted->getArgOne();
            Assert::IsTrue(argOne == "a1");

            // Check if relation enum is still the same
            Assert::IsTrue(clauseReverted->getRel() == Relationship::USES);
        }

        TEST_METHOD(TestRevertToActualClauseType_sharedPtr) {
            list<string> actualSynonyms;
            list<string> expectedSynonyms;

            // Create a sample "such that" clause
            SuchThatClausePtr uses_a1_v1_ptr(new SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1"));

            // Put the sample clause in a queue of the parent type, then take it out and cast back
            queue<ClausePtr> clauseQueue;
            clauseQueue.push(uses_a1_v1_ptr);

            ClausePtr clausePtr = clauseQueue.front();

            SuchThatClausePtr clauseRevertedPtr;
            clauseRevertedPtr = dynamic_pointer_cast<SuchThatClause>(clausePtr);

            // Check if variables are still the same
            actualSynonyms = clauseRevertedPtr->getSynonyms();
            expectedSynonyms = list<string>{ "a1", "v1" };
            actualSynonyms.sort();
            expectedSynonyms.sort();
            Assert::IsTrue(actualSynonyms == expectedSynonyms);

            // Test retrieving first argument
            string argOne = clauseRevertedPtr->getArgOne();
            Assert::IsTrue(argOne == "a1");

            // Check if relation enum is still the same
            Assert::IsTrue(clauseRevertedPtr->getRel() == Relationship::USES);
        }

        TEST_METHOD(TestRevertToActualClauseType_dynamicCast) {
            list<string> actualSynonyms;
            list<string> expectedSynonyms;

            SuchThatClause* uses_a1_v1 = new SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            queue<Clause*> clauseQueue;
            clauseQueue.push(uses_a1_v1);

            Clause* clausePtr = clauseQueue.front();

            SuchThatClause* clauseReverted = dynamic_cast<SuchThatClause*>(clausePtr);
            Assert::IsTrue(clauseReverted != NULL);

            actualSynonyms = clauseReverted->getSynonyms();
            expectedSynonyms = list<string>{ "a1", "v1" };
            actualSynonyms.sort();
            expectedSynonyms.sort();
            Assert::IsTrue(actualSynonyms == expectedSynonyms);

            Assert::IsTrue(clauseReverted->getRel() == Relationship::USES);
            delete uses_a1_v1;
        }
    };
}