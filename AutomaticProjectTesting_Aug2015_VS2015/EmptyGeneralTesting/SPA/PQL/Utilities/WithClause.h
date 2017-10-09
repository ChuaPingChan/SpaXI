#pragma once
#include <string>
#include "../Attributeship.h"

class WithClause
{
public:
    WithClause(Attribute lhsAttribute, string lhsValue, Attribute rhsAttribute, string rhsValue);
    ~WithClause();

    Attribute getLhsAttribute();
    Attribute getRhsAttribute();
    string getLhsValue();
    string getRhsValue();

private:
    Attribute lhsAttribute;
    Attribute rhsAttribute;
    string lhsValue;
    string rhsValue;
};

