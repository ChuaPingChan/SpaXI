#include <cassert>

#include "ClauseWrapper.h"
#include "SuchThatClause.h"
#include "PatternClause.h"
#include "WithClause.h"

ClauseWrapper::ClauseWrapper(SelectClause &clause)
{
    _clauseCategory = ClauseCategory::SELECT;

    SelectionType selectiontype = clause.getSelectionType();
    if (selectiontype == SelectionType::SELECT_BOOLEAN) {
        _selectClausePtr = new SelectClause(selectiontype);
    } else if (selectiontype == SelectionType::SELECT_SINGLE) {
        _selectClausePtr = new SelectClause(selectiontype, clause.getSingleArgType(), clause.getSingleArg());
    } else {
        assert(selectiontype == SelectionType::SELECT_TUPLE);
        _selectClausePtr = new SelectClause(selectiontype, clause.getTupleArgTypes(), clause.getTupleArgs());
    }
}

ClauseWrapper::ClauseWrapper(SuchThatClause &clause)
{
    _clauseCategory = ClauseCategory::SUCH_THAT;

    _suchThatClausePtr = new SuchThatClause(clause.getRel(), clause.getArgOneType(), clause.getArgOne(),
        clause.getArgTwoType(), clause.getArgTwo());
}

ClauseWrapper::ClauseWrapper(PatternClause &clause)
{
    _clauseCategory = ClauseCategory::PATTERN;

    PatternType patternType = clause.getPatternType();
    if (patternType == PatternType::ASSIGN_PATTERN || patternType == PatternType::WHILE_PATTERN) {
        _patternClausePtr = new PatternClause(patternType, clause.getPatternSynonym(),
            clause.getArgOneType(), clause.getArgOne(), clause.getArgTwoType(), clause.getArgTwo());
    } else {
        assert(patternType == PatternType::IF_PATTERN);
        _patternClausePtr = new PatternClause(patternType, clause.getPatternSynonym(),
            clause.getArgOneType(), clause.getArgOne(), clause.getArgTwoType(), clause.getArgTwo(),
            clause.getArgThreeType(), clause.getArgThree());
    }
}

ClauseWrapper::ClauseWrapper(WithClause &clause)
{
    _clauseCategory = ClauseCategory::WITH;
    _withClausePtr = new WithClause(clause.getWithType(), clause.getLhsEntity(), clause.getLhsValue(),
        clause.getRhsEntity(), clause.getRhsValue());
}

ClauseWrapper::~ClauseWrapper()
{
    //if (_selectClausePtr != NULL)
    //    delete _selectClausePtr;
    //if (_suchThatClausePtr != NULL)
    //    delete _suchThatClausePtr;
    //if (_patternClausePtr != NULL)
    //    delete _patternClausePtr;
    //if (_withClausePtr != NULL)
    //    delete _withClausePtr;
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
