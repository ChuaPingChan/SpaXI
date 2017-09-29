#include "Relationship.h"



Relationship::Relationship()
{
}

Relationship::Relationship(ARGUMENT arg1Type, ARGUMENT arg2Type)
{
    this->arg1Type = arg1Type;
    this->arg2Type = arg2Type;
}

Relationship::Relationship(ARGUMENT arg1Type, ARGUMENT arg2Type, ARGUMENT arg3Type)
{
    this->arg1Type = arg1Type;
    this->arg2Type = arg2Type;
    this->arg3Type = arg3Type;
}

ARGUMENT Relationship::getArg1Type() {
    return arg1Type;
}

ARGUMENT Relationship::getArg2Type() {
    return arg2Type;
}

ARGUMENT Relationship::getArg3Type() {
    return arg3Type;
}

Relationship::~Relationship()
{
}
