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

    TEST_CLASS(TestOptimizer)
    {
    public:

        TEST_METHOD(TestAllMethods1) {

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

            QueryTree qTree;
            qTree.insertSelect(select_a1);
            qTree.insertSuchThat(uses_a1_v1);
            qTree.insertSuchThat(modifies_w1_v1);
            qTree.insertSuchThat(uses_a2_v2);
            qTree.insertSuchThat(uses_10_ident);

            /***********
            * Testing *
            ***********/

            // TODO: Change this unit test. Assertions will fail after intra-clause group sorting is implemented.
            Optimizer optimizer(qTree);
            ClauseGroupManager clauseGroupManager = optimizer.getClauseGroupManager();
            
            queue<ClausePtr> nextClauseGroup;
            ClausePtr tempClausePtr;
            SelectClausePtr tempScPtr;
            SuchThatClausePtr tempStcPtr;
            PatternClausePtr tempPcPtr;
            WithClausePtr tempWcPtr;

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            tempClausePtr = nextClauseGroup.front();
            Assert::IsTrue(tempClausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            tempStcPtr = dynamic_pointer_cast<SuchThatClause>(tempClausePtr);
            Assert::IsTrue(tempStcPtr->getRel() == Relationship::USES);
            Assert::IsTrue(tempStcPtr->getArgOneType() == Entity::INTEGER);
            Assert::IsTrue(tempStcPtr->getArgTwoType() == Entity::IDENT_WITHQUOTES);
            Assert::IsTrue(tempStcPtr->getArgOne() == "10");
            Assert::IsTrue(tempStcPtr->getArgTwo() == "dummyVar");

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 1);
            tempClausePtr = nextClauseGroup.front();
            Assert::IsTrue(tempClausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            tempStcPtr = dynamic_pointer_cast<SuchThatClause>(tempClausePtr);
            Assert::IsTrue(tempStcPtr->getRel() == Relationship::USES);
            Assert::IsTrue(tempStcPtr->getArgOneType() == Entity::ASSIGN);
            Assert::IsTrue(tempStcPtr->getArgTwoType() == Entity::VARIABLE);
            Assert::IsTrue(tempStcPtr->getArgOne() == "a2");
            Assert::IsTrue(tempStcPtr->getArgTwo() == "v2");

            nextClauseGroup = clauseGroupManager.getNextClauseGroup();
            Assert::IsTrue(nextClauseGroup.size() == 2);
            tempClausePtr = nextClauseGroup.front();
            Assert::IsTrue(tempClausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            tempStcPtr = dynamic_pointer_cast<SuchThatClause>(tempClausePtr);
            Assert::IsTrue(tempStcPtr->getRel() == Relationship::MODIFIES);
            Assert::IsTrue(tempStcPtr->getArgOneType() == Entity::WHILE);
            Assert::IsTrue(tempStcPtr->getArgTwoType() == Entity::VARIABLE);
            Assert::IsTrue(tempStcPtr->getArgOne() == "w1");
            Assert::IsTrue(tempStcPtr->getArgTwo() == "v1");
            nextClauseGroup.pop();
            tempClausePtr = nextClauseGroup.front();
            Assert::IsTrue(tempClausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT);
            tempStcPtr = dynamic_pointer_cast<SuchThatClause>(tempClausePtr);
            Assert::IsTrue(tempStcPtr->getRel() == Relationship::USES);
            Assert::IsTrue(tempStcPtr->getArgOneType() == Entity::ASSIGN);
            Assert::IsTrue(tempStcPtr->getArgTwoType() == Entity::VARIABLE);
            Assert::IsTrue(tempStcPtr->getArgOne() == "a1");
            Assert::IsTrue(tempStcPtr->getArgTwo() == "v1");
            nextClauseGroup.pop();

            Assert::IsFalse(clauseGroupManager.hasNextClauseGroup());
        }
    };
}
