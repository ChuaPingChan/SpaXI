#include "ClauseCostCalculator.h"

#include <cassert>
#include <unordered_map>

ClauseCostCalculator::ClauseCostCalculator()
{
}

int ClauseCostCalculator::getCost(ClausePtr clausePtr)
{
    Clause::ClauseType clauseType = clausePtr->getClauseType();

    if (clauseType == Clause::ClauseType::SUCH_THAT) {
        SuchThatClausePtr stcPtr;
        stcPtr = dynamic_pointer_cast<SuchThatClause>(clausePtr);
        return getCost(stcPtr);
    } else if (clauseType == Clause::ClauseType::PATTERN) {
        PatternClausePtr pcPtr;
        pcPtr = dynamic_pointer_cast<PatternClause>(clausePtr);
        return getCost(pcPtr);
    } else if (clauseType == Clause::ClauseType::WITH) {
        WithClausePtr wcPtr;
        wcPtr = dynamic_pointer_cast<WithClause>(clausePtr);
        return getCost(wcPtr);
    } else if (clauseType == Clause::ClauseType::SELECT) {
        SelectClausePtr scPtr;
        scPtr = dynamic_pointer_cast<SelectClause>(clausePtr);
        return getCost(scPtr);
    } else {
        assert(false);  // Shouldn't reach here
    }
}

int ClauseCostCalculator::getCost(SelectClausePtr selectClausePtr)
{
    // Assumes that a select-clause will always have >= 1 synonym, because select
    // BOOLEAN will not be added into clause groups
    list<string> synonyms = selectClausePtr->getSynonyms();
    assert(synonyms.size() > 0);

    if (synonyms.size() == 1)
        return ClauseCostCalculator::SELECT_1ARG;
    else
        return ClauseCostCalculator::SELECT_TUPLE;
    return 0;
}

int ClauseCostCalculator::getCost(SuchThatClausePtr suchThatClausePtr)
{
    list<string> synonyms = suchThatClausePtr->getSynonyms();
    Relationship rel = suchThatClausePtr->getRel();

    switch (rel) {
    case Relationship::FOLLOWS:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::FOLLOWS_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::FOLLOWS_1ARG;
        } else {
            assert(synonyms.size() == 2);
            return ClauseCostCalculator::ClauseCost::FOLLOWS_2ARGS;
        }
        break;
    case Relationship::FOLLOWSSTAR:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::FOLLOWS_STAR_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::FOLLOWS_STAR_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::FOLLOWS_STAR_2ARGS;
        }
        break;
    case Relationship::USES:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::USES_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::USES_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::USES_2ARGS;
        }
        break;
    case Relationship::MODIFIES:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::MODIFIES_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::MODIFIES_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::MODIFIES_2ARGS;
        }
        break;
    case Relationship::PARENT:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::PARENT_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::PARENT_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::PARENT_2ARGS;
        }
        break;
    case Relationship::PARENTSTAR:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::PARENT_STAR_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::PARENT_STAR_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::PARENT_STAR_2ARGS;
        }
        break;
    case Relationship::CALLS:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::CALLS_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::CALLS_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::CALLS_2ARGS;
        }
        break;
    case Relationship::CALLSSTAR:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::CALLS_STAR_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::CALLS_STAR_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::CALLS_STAR_2ARGS;
        }
        break;
    case Relationship::NEXT:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::NEXT_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::NEXT_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::NEXT_2ARGS;
        }
        break;
    case Relationship::NEXTSTAR:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::NEXT_STAR_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::NEXT_STAR_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::NEXT_2ARGS;
        }
        break;
    case Relationship::AFFECTS:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_2ARGS;
        }
        break;
    case Relationship::AFFECTSSTAR:
        if (synonyms.empty()) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_STAR_BOOLEAN;
        } else if (synonyms.size() == 1) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_STAR_1ARG;
        } else if (synonyms.size() == 2) {
            return ClauseCostCalculator::ClauseCost::AFFECTS_STAR_2ARGS;
        }
        break;
    default:
        assert(false);  // Shouldn't reach here
    }
}

int ClauseCostCalculator::getCost(PatternClausePtr patternClausePtr)
{
    return ClauseCostCalculator::ClauseCost::PATTERN_ANY_ARGS;
}

int ClauseCostCalculator::getCost(WithClausePtr withClausePtr)
{
    // Assumes that a with-clause received always has synonyms, because of validator's processing
    assert((withClausePtr->getSynonyms()).size() > 0);
    return ClauseCostCalculator::ClauseCost::WITH_ANY_ARGS;
}
