#pragma once
#include <string>
#include "..\..\Entity.h"
#include "..\Withship.h"
#include "Clause.h"

class WithClause : public Clause
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

