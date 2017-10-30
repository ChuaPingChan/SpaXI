#include "CppUnitTest.h"
#include <string>

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

        TEST_METHOD(TestSynonymInitialization) {
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
    };
}