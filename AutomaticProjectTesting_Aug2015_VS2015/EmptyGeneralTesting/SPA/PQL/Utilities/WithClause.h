#pragma once
#include <string>
#include "..\..\Entity.h"
#include "..\Attributeship.h"

class WithClause
{
public:
    WithClause(WithType withType, Entity lhsEntity, string lhsValue, Entity rhsEntity, string rhsValue);
    ~WithClause();

    WithType getWithType();
    Entity getLhsEntity();
    Entity getRhsEntity();
    string getLhsValue();
    string getRhsValue();

private:
    WithType withType;
    Entity lhsEntity;
    Entity rhsEntity;
    string lhsValue;
    string rhsValue;
};

