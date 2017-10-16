#include "WithClause.h"

WithClause::WithClause(WithType withType, Entity lhsEntity, string lhsValue, Entity rhsEntity, string rhsValue)
{
    this->withType = withType;
    this->lhsEntity = lhsEntity;
    this->lhsValue = lhsValue;
    this->rhsEntity = rhsEntity;
    this->rhsValue = rhsValue;
}

WithClause::~WithClause()
{
}

WithType WithClause::getWithType()
{
    return this->withType;
}

Entity WithClause::getLhsEntity()
{
    return this->lhsEntity;
}

Entity WithClause::getRhsEntity()
{
    return this->rhsEntity;
}

string WithClause::getLhsValue()
{
    return this->lhsValue;
}

string WithClause::getRhsValue()
{
    return this->rhsValue;
}
