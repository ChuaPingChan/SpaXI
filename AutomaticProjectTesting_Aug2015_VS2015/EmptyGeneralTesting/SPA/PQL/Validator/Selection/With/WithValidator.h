#pragma once
#include <string>
#include "..\..\..\QueryTree.h"
#include "..\..\..\Attributeship.h"
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\..\Exceptions\SynonymNotFoundException.h"
#include "..\..\..\..\Exceptions\AttributeNotFoundException.h"

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
    static const string ATTRIBUTE_STRING[];
    QueryTree *qtPtr;

    Attribute lhsAttribute;
    Attribute rhsAttribute;
    string lhsValue;
    string rhsValue;
    bool validity = false;

    string extractLhs(string str);
    string extractRhs(string str);
    bool isValidLhs(string lhs);
    bool isValidRhs(string rhs);

    bool isIntegerType(Attribute attr);
    bool isStringType(Attribute attr);
    bool isLhsSameTypeAsRhs();

    Entity getEntityOfSynonym(string syn);
    Attribute getAttributeOfAttrRefAttribute(Entity entity, string attr);

    string getAttrRefSynonymStr(string str);
    string getAttrRefAttributeStr(string str);
};
