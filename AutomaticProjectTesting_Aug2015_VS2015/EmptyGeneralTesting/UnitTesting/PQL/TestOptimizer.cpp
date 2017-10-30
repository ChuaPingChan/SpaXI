#include "CppUnitTest.h"
#include <string>
#include <unordered_set>

#include "../SPA/PQL/Optimizer/Optimizer.h"
#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/Optimizer/ClauseGroupManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestOptimizer)
    {
    public:

        TEST_METHOD(TestMultiMethods_success) {
            /*
                Query:
                assign a1, a2; stmt s1, s2;
                while w1, w2; if i1, iw; call cl1, cl2;
                procedure p1, p2; prog_line pl1, pl2;
                variable v1, v2; constant c1, c2;

                Select s1
                such that Uses(a1, v1)
                such that Modifies (w1, v1)
                such that Uses (a2, v2)
            */
            QueryTree qt = QueryTree();
            SuchThatClause uses_a1_v1 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a1",
                Entity::VARIABLE, "v1");
            SuchThatClause modifies_w1_v1 = SuchThatClause(Relationship::MODIFIES,
                Entity::WHILE, "w1",
                Entity::VARIABLE, "v1");
            SuchThatClause uses_a2_v2 = SuchThatClause(Relationship::USES,
                Entity::ASSIGN, "a2",
                Entity::VARIABLE, "v2");
            SuchThatClause uses_10_ident = SuchThatClause(Relationship::USES,
                Entity::INTEGER, "10",
                Entity::IDENT_WITHQUOTES, "dummyVar");

            qt.insertSuchThat(uses_a1_v1);
            qt.insertSuchThat(modifies_w1_v1);
            qt.insertSuchThat(uses_a2_v2);
            qt.insertSuchThat(uses_10_ident);

            Optimizer optimizer(qt);
            ClauseGroupManager clauseGroupManager = optimizer.getClauseGroupManager();
            queue<ClauseWrapper> nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            //Assert::IsTrue(nextClauseGroup)

        }
    };
}