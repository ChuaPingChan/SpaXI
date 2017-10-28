#include <cassert>

#include "ClauseWrapper.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "WithClause.h"

ClauseWrapper::ClauseWrapper(SelectClause & clause)
{
    _clauseCategory = ClauseCategory::SELECT;
    _selectClausePtr = &clause;
}

ClauseWrapper::ClauseWrapper(SuchThatClause &clause)
{
    _clauseCategory = ClauseCategory::SUCH_THAT;
    _suchThatClausePtr = &clause;
}

ClauseWrapper::ClauseWrapper(PatternClause &clause)
{
    _clauseCategory = ClauseCategory::PATTERN;
    _patternClausePtr = &clause;
}

ClauseWrapper::ClauseWrapper(WithClause &clause)
{
    _clauseCategory = ClauseCategory::WITH;
    _withClausePtr = &clause;
}

/*
    This is a private constructor used only to initialise private members.
    When this constructor finishes, ClauseWrapper is not ready for use yet.
*/
ClauseWrapper::ClauseWrapper()
{
    _selectClausePtr = NULL;
    _suchThatClausePtr = NULL;
    _patternClausePtr = NULL;
    _withClausePtr = NULL;
}

bool ClauseWrapper::isSelectClause()
{
    return _clauseCategory == ClauseCategory::SELECT;
}

bool ClauseWrapper::isSuchThatClause()
{
    return _clauseCategory == ClauseCategory::SUCH_THAT;
}

bool ClauseWrapper::isPatternClause()
{
    return _clauseCategory == ClauseCategory::PATTERN;
}

bool ClauseWrapper::isWithClause()
{
    return _clauseCategory == ClauseCategory::WITH;
}

/*
    Returns the clause stored in the wrapper in the form of the superclass Clause.
*/
Clause ClauseWrapper::getClause()
{
    return Clause();
}

/*
Returns the "select" clause stored in the wrapper.
Pre-condition:
Ensure wrapper stores a "select" clause using the isSelectClause() method.
*/
SelectClause ClauseWrapper::getSelectClause()
{
    assert(isSelectClause());
    return *_selectClausePtr;
}

/*
    Returns the "such that" clause stored in the wrapper.
    Pre-condition:
        Ensure wrapper stores a "such that" clause using the isSuchThatClause() method.
*/
SuchThatClause ClauseWrapper::getSuchThatClause()
{
    assert(isSuchThatClause());
    return *_suchThatClausePtr;
}

/*
    Returns the "pattern" clause stored in the wrapper.
    Pre-condition:
        Ensure wrapper stores a "pattern" clause using the isPatternClause() method.
*/
PatternClause ClauseWrapper::getPatternClause()
{
    assert(isPatternClause());
    return *_patternClausePtr;
}

/*
    Returns the "with " clause stored in the wrapper.
    Pre-condition:
        Ensure wrapper stores a "with" clause using the isWithClause() method.
*/
WithClause ClauseWrapper::getWithClause()
{
    assert(isWithClause());
    return *_withClausePtr;
}
