#include "WithClause.h"

WithClause::WithClause(Attribute lhsAttribute, string lhsValue, Attribute rhsAttribute, string rhsValue)
{
    this->lhsAttribute = lhsAttribute;
    this->lhsValue = lhsValue;
    this->rhsAttribute = rhsAttribute;
    this->rhsValue = rhsValue;
}

WithClause::~WithClause()
{
}

Attribute WithClause::getLhsAttribute()
{
    return this->lhsAttribute;
}

Attribute WithClause::getRhsAttribute()
{
    return this->rhsAttribute;
}

string WithClause::getLhsValue()
{
    return this->lhsValue;
}

string WithClause::getRhsValue()
{
    return this->rhsValue;
}
