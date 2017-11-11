#include "SuchThatClause.h"
#include "../../Entity.h"
#include "Clause.h"


SuchThatClause::SuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
    : Clause(Clause::ClauseType::SUCH_THAT)
{
    this->_rel = rel;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_argOne = argOne;
    this->_argTwo = argTwo;

    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
    if (entityIsSynonym(argTwoType)) {
        addSynonym(argTwo);
    }
}

SuchThatClausePtr SuchThatClause::getSharedPtr()
{
    return SuchThatClausePtr(new SuchThatClause(getRel(), getArgOneType(), getArgOne(),
        getArgTwoType(), getArgTwo()));
}


SuchThatClause::~SuchThatClause()
{
}

Relationship SuchThatClause::getRel()
{
    return this->_rel;
}

Entity SuchThatClause::getArgOneType()
{
    return this->_argOneType;
}

Entity SuchThatClause::getArgTwoType()
{
    return this->_argTwoType;
}

string SuchThatClause::getArgOne()
{
    return this->_argOne;
}

string SuchThatClause::getArgTwo()
{
    return this->_argTwo;
}
