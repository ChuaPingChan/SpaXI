#include <cassert>
#include "QueryEvaluator.h"
#include "../Optimizer/Optimizer.h"
#include "../Optimizer/ClauseGroup.h"
#include "../Optimizer/ClauseGroupManager.h"

QueryEvaluator::QueryEvaluator(QueryTree* qtPtr)
{
    this->_qt = qtPtr;
    hasResultEvaluator = true;
}

QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
    ResultFactory factory = ResultFactory();
    Optimizer optimizer(*_qt);
    ClauseGroupManager clauseGroupManager = optimizer.getClauseGroupManager();

    // For each clause groups..
    while (hasResultEvaluator && clauseGroupManager.hasNextClauseGroup()) {

        ClauseGroup clauseGroup = clauseGroupManager.getNextClauseGroup();

        // For each clause in a clause group..
        while (hasResultEvaluator && clauseGroup.hasNextClause()) {
            
            ClausePtr clausePtr = clauseGroup.getNextClause();

            // Checks for the actual type of clause and do type-conversion to use subclass's methods
            if (clausePtr->getClauseType() == Clause::ClauseType::SUCH_THAT) {
                SuchThatClausePtr stClausePtr = dynamic_pointer_cast<SuchThatClause>(clausePtr);
                hasResultEvaluator = factory.processClause(*stClausePtr);
            } else if (clausePtr->getClauseType() == Clause::ClauseType::PATTERN) {
                PatternClausePtr pattClausePtr = dynamic_pointer_cast<PatternClause>(clausePtr);
                hasResultEvaluator = factory.processClause(*pattClausePtr);
            } else if (clausePtr->getClauseType() == Clause::ClauseType::WITH) {
                WithClausePtr withClausePtr = dynamic_pointer_cast<WithClause>(clausePtr);
                hasResultEvaluator = factory.processClause(*withClausePtr);
            } else {
                // This assertion might need to be changed if new clause types are introduced to SIMPLE
                assert(clausePtr->getClauseType() == Clause::ClauseType::SELECT);
                SelectClausePtr selectClausePtr = dynamic_pointer_cast<SelectClause>(clausePtr);
                hasResultEvaluator = factory.processClause(*selectClausePtr);
            }

            clauseGroup.pruneClauseResult(factory.getClauseResultPtr());
        }
        
        // Finished processing a clause group, pass the result of the clause group to ClauseGroupManager
        ClauseResult clauseResult = factory.makeClauseResult();
        clauseGroupManager.mergeClauseResult(clauseResult);
        factory.resetClauseResult();
    }

    // Store result in query tree
    if (hasResultEvaluator)
    {
        _qt->storeEvaluatorResult(clauseGroupManager.getMergedClauseResult());
    }
}

bool QueryEvaluator::hasResult()
{
    return hasResultEvaluator;
}
