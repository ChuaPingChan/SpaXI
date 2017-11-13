#include <cassert>
#include <iostream>
#include "QueryEvaluator.h"
#include "../Optimizer/Optimizer.h"
#include "../Optimizer/ClauseGroup.h"
#include "../Optimizer/ClauseGroupManager.h"
#include "AbstractWrapper.h"

QueryEvaluator::QueryEvaluator(QueryTree* qtPtr)
{
    this->_qt = qtPtr;
    _hasResult = true;
}

QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
    try {
        ResultFactory factory = ResultFactory();
        Optimizer optimizer(*_qt);
        ClauseGroupManager clauseGroupManager = optimizer.getClauseGroupManager();

        // For each clause groups..
        while (_hasResult && clauseGroupManager.hasNextClauseGroup()) {

            ClauseGroup clauseGroup = clauseGroupManager.getNextClauseGroup();

            // For each clause in a clause group..
            while (_hasResult && clauseGroup.hasNextClause()) {

                ClausePtr clausePtr = clauseGroup.getNextClause();
                Clause::ClauseType clauseType = clausePtr->getClauseType();

                // Checks for the type of clause and perform downcasting to use methods of the child classes
                if (clauseType == Clause::ClauseType::SUCH_THAT)
                {
                    SuchThatClausePtr stClausePtr = dynamic_pointer_cast<SuchThatClause>(clausePtr);
                    _hasResult = factory.processClause(*stClausePtr);
                }

                else if (clauseType == Clause::ClauseType::PATTERN)
                {
                    PatternClausePtr pattClausePtr = dynamic_pointer_cast<PatternClause>(clausePtr);
                    _hasResult = factory.processClause(*pattClausePtr);
                }

                else if (clauseType == Clause::ClauseType::WITH)
                {
                    WithClausePtr withClausePtr = dynamic_pointer_cast<WithClause>(clausePtr);
                    _hasResult = factory.processClause(*withClausePtr);
                }

                else if (clauseType == Clause::ClauseType::SELECT)
                {
                    SelectClausePtr selectClausePtr = dynamic_pointer_cast<SelectClause>(clausePtr);
                    _hasResult = factory.processClause(*selectClausePtr);
                }

                else
                {
                    throw UnrecognisedTypeException("in QueryEvaluator. ClauseType: " + to_string(clauseType));
                }

                // Check for timeout
                if (AbstractWrapper::GlobalStop) {
                    _hasResult = false;
                    return;
                }

                clauseGroup.pruneClauseResult(factory.getClauseResultPtr());
            }

            // Finished processing a clause group, pass the result of the clause group to ClauseGroupManager
            ClauseResult clauseResult = factory.makeClauseResult();
            clauseGroupManager.mergeClauseResult(clauseResult);
            factory.resetClauseResult();
        }

        // Store result in query tree
        if (_hasResult)
        {
            _qt->storeEvaluatorResult(clauseGroupManager.getMergedClauseResult());
        }
    }

    catch (UnrecognisedTypeException& e) {
        cerr << e.what() << endl;
    }
}

bool QueryEvaluator::hasResult()
{
    return _hasResult;
}
