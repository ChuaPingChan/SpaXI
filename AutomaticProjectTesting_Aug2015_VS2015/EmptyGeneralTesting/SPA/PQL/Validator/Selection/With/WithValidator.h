#pragma once
#include <string>
#include "..\..\..\QueryTree.h"
#include "..\..\..\Attributeship.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

class WithValidator
{
public:
    WithValidator(QueryTree *qtPtrNew);
    ~WithValidator();

    void validate(string str);
    bool isValid();

    Attribute getLhsAttribute();
    Attribute getRhsAttribute();
    string getLhsValue();
    string getRhsValue();

private:
    QueryTree *qtPtr;

    Attribute lhsAttribute;
    Attribute rhsAttribute;
    string lhsValue;
    string rhsValue;
    bool validity = false;

    string extractLhs(string str);
    string extractRhs(string str);
    void determineLhsAttributeAndValue(string str);
    void determineRhsAttributeAndValue(string str);
};

