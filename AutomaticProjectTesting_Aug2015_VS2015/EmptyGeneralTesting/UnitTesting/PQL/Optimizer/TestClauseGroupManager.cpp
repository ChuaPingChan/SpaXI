#include "CppUnitTest.h"
#include <string>
#include <queue>

#include "../SPA/PQL/Optimizer/Optimizer.h"
#include "../SPA/PQL/QueryTree.h"
#include "../SPA/PQL/Utilities/Clause.h"
#include "../SPA/PQL/Utilities/SuchThatClause.h"
#include "../SPA/PQL/Utilities/PatternClause.h"
#include "../SPA/PQL/Utilities/WithClause.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestClauseGroupManager)
    {
    public:

        TEST_METHOD(TestSetAndGetNextClauseGroup) {
            
            /**********
             * Set up *
             **********/
            /*
                Query:
                assign a1, a2; stmt s1, s2;
                while w1, w2; if i1, if2; while w1, w2; call cl1, cl2;
                procedure p1, p2; prog_line pl1, pl2;
                variable v1, v2; constant c1, c2;

                Select a1
                such that Uses(a1, v1)
                such that Modifies(w1, v1)
                such that Uses(a2, v2)
                such that Uses(10, "dummyVar")
            */

            SelectClause select_a1 = SelectClause(SelectionType::SELECT_SINGLE, Entity::ASSIGN, "a1");
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

            SelectClausePtr select_a1_ptr;
            SuchThatClausePtr uses_a1_v1_ptr;
            SuchThatClausePtr modifies_w1_v1_ptr;
            SuchThatClausePtr uses_a2_v2_ptr;
            SuchThatClausePtr uses_10_ident_ptr;
            select_a1_ptr = select_a1.getSharedPtr();
            uses_a1_v1_ptr = uses_a1_v1.getSharedPtr();
            modifies_w1_v1_ptr = modifies_w1_v1.getSharedPtr();
            uses_a2_v2_ptr = uses_a2_v2.getSharedPtr();
            uses_10_ident_ptr = uses_10_ident.getSharedPtr();

            queue<queue<ClausePtr>> tempClauseGroupQueue;
            queue<ClausePtr> tempClauseGroup;

            tempClauseGroup.push(uses_10_ident_ptr);
            tempClauseGroupQueue.push(tempClauseGroup);
            
            tempClauseGroup = queue<ClausePtr>();
            tempClauseGroup.push(uses_a1_v1_ptr);
            tempClauseGroup.push(modifies_w1_v1_ptr);
            tempClauseGroupQueue.push(tempClauseGroup);
            
            tempClauseGroup = queue<ClausePtr>();
            tempClauseGroup.push(uses_a2_v2_ptr);
            tempClauseGroupQueue.push(tempClauseGroup);

            /***********
             * Testing *
             ***********/
            ClauseGroupManager clauseGroupManager;
            clauseGroupManager.setClauseGroupQueue(tempClauseGroupQueue);

            queue<ClausePtr> nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            Assert::IsTrue(nextClauseGroup.front() == uses_10_ident_ptr);
            
            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 2);
            Assert::IsTrue(nextClauseGroup.front() == uses_a1_v1_ptr);
            nextClauseGroup.pop();
            Assert::IsTrue(nextClauseGroup.front() == modifies_w1_v1_ptr);

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            Assert::IsTrue(nextClauseGroup.front() == uses_a2_v2_ptr);

            Assert::IsFalse(clauseGroupManager.hasNextClauseGroup());
        }
    };
}