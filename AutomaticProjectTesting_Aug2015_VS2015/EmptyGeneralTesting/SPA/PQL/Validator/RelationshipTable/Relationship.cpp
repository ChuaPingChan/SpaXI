#include "Relationship.h"



Relationship::Relationship()
{
}

Relationship::Relationship(ARGUMENT argType1, ARGUMENT argType2)
{
    this->argType1 = argType1;
    this->argType2 = argType2;
}

Relationship::Relationship(ARGUMENT arg1, ARGUMENT arg2, ARGUMENT arg3)
{
    this->argType1 = argType1;
    this->argType2 = argType2;
    this->argType3 = argType3;
}


Relationship::~Relationship()
{
}
