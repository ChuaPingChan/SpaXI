#include "WithClause.h"



WithClause::WithClause()
{
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
