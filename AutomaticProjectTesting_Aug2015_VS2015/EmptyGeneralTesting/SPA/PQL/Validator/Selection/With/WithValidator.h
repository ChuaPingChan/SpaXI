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

    WithType getLhsWithType();
    Entity getLhsEntity();
    string getLhsValue();

    WithType getRhsWithType();
    Entity getRhsEntity();
    string getRhsValue();

private:
    static const string ATTRIBUTE_STRING[];
    QueryTree *qtPtr;

    WithType lhsWithType;
    Entity lhsEntity;
    string lhsValue;

    WithType rhsWithType;
    Entity rhsEntity;
    string rhsValue;

    bool validity = false;

    string extractLhs(string str);
    string extractRhs(string str);
    bool isValidLhs(string lhs);
    bool isValidRhs(string rhs);

    bool isLhsSameTypeAsRhs();

    Entity getEntityOfSynonym(string syn);
    WithType getWithType(Entity entity, string attr);

    string getAttrRefSynonymStr(string str);
    string getAttrRefAttributeStr(string str);
};
