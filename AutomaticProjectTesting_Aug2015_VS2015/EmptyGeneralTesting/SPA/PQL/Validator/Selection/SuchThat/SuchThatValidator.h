#pragma once
#include <string>
#include <unordered_set>
#include <regex>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\..\QueryTree.h"
#include "..\..\..\Relationship.h"
#include "..\..\..\..\Entity.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"

using namespace std;

/**
* Super class of all suchthat validators
*/
class SuchThatValidator
{
public:
    SuchThatValidator(Relationship rel, string paramStr, QueryTree *qtPtrNew);
    SuchThatValidator();
    ~SuchThatValidator();

    virtual void validate();
    virtual bool isValid();

    Relationship getRel();
    Entity getArgOneType();
    Entity getArgTwoType();
    string getArgOne();
    string getArgTwo();

protected:
    static const string UNDERSCORE_STRING;
    QueryTree *qtPtr;
    string paramStr;

    Relationship rel;
    Entity argOneType;
    Entity argTwoType;
    string argOne = "";
    string argTwo = "";
    bool validity = false;

    string extractArgOne(Relationship rel, string str);
    string extractArgTwo(string str);
};
