#include "Relationship.h"



Relationship::Relationship()
{
}

Relationship::Relationship(ARGUMENT_TYPE_RULES arg1Type, ARGUMENT_TYPE_RULES arg2Type)
{
    this->arg1Type = arg1Type;
    this->arg2Type = arg2Type;
}

Relationship::Relationship(ARGUMENT_TYPE_RULES arg1Type, ARGUMENT_TYPE_RULES arg2Type, ARGUMENT_TYPE_RULES arg3Type)
{
    this->arg1Type = arg1Type;
    this->arg2Type = arg2Type;
    this->arg3Type = arg3Type;
}

ARGUMENT_TYPE_RULES Relationship::getArg1Type() {
    return arg1Type;
}

ARGUMENT_TYPE_RULES Relationship::getArg2Type() {
    return arg2Type;
}

ARGUMENT_TYPE_RULES Relationship::getArg3Type() {
    return arg3Type;
}

Relationship::~Relationship()
{
}
