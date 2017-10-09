#pragma once
#include <string>
#include "../Attributeship.h"

class WithClause
{
public:
    WithClause();
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

