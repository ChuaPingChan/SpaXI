#include <cassert>
#include "PatternClause.h"
#include "../../Entity.h"

using namespace std;

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
    : Clause(Clause::ClauseType::PATTERN)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;

    addSynonym(patternSyn);
    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
}

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree)
    : Clause(Clause::ClauseType::PATTERN)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_argThreeType = argThreeType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;
    this->_argThree = argThree;

    addSynonym(patternSyn);
    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
}

PatternClause::~PatternClause()
{
}

PatternClausePtr PatternClause::getSharedPtr()
{
    if (getPatternType() == PatternType::ASSIGN_PATTERN
        || getPatternType() == PatternType::WHILE_PATTERN) {
        return PatternClausePtr(new PatternClause(getPatternType(), getPatternSynonym(),
            getArgOneType(), getArgOne(), getArgTwoType(), getArgTwo()));
    } else {
        assert(getPatternType() == PatternType::IF_PATTERN);
        return PatternClausePtr(new PatternClause(getPatternType(), getPatternSynonym(),
            getArgOneType(), getArgOne(), getArgTwoType(), getArgTwo(), getArgThreeType(), getArgThree()));
    }
}

PatternType PatternClause::getPatternType()
{
    return _patternType;
}

Entity PatternClause::getArgOneType()
{
    return this->_argOneType;
}

Entity PatternClause::getArgTwoType()
{
    return this->_argTwoType;
}

Entity PatternClause::getArgThreeType()
{
    return this->_argThreeType;
}

string PatternClause::getPatternSynonym()
{
    return this->_patternSyn;
}

string PatternClause::getArgOne()
{
    return this->_argOne;
}

string PatternClause::getArgTwo()
{
    return this->_argTwo;
}

string PatternClause::getArgThree()
{
    return this->_argThree;
}
