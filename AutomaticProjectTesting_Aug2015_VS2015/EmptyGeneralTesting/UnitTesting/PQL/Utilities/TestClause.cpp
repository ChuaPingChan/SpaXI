#include "CppUnitTest.h"
#include <string>
#include <queue>

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

            SuchThatClause* uses_a1_v1 = new SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");

            queue<Clause*> clauseQueue;
            clauseQueue.push(uses_a1_v1);

            Clause* clausePtr = clauseQueue.front();

            SuchThatClause* clauseReverted = static_cast<SuchThatClause*>(clausePtr);
            Assert::IsTrue(clauseReverted != NULL);

            actualSynonyms = clauseReverted->getSynonyms();
            expectedSynonyms = list<string>{ "a1", "v1" };
            actualSynonyms.sort();
            expectedSynonyms.sort();
            Assert::IsTrue(actualSynonyms == expectedSynonyms);

            Assert::IsTrue(clauseReverted->getRel() == Relationship::USES);
            delete uses_a1_v1;
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