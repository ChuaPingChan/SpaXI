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
    static const int UNKNWON = -1;
    QueryTree *qtPtr;
    string paramStr;

    //TODO: Might need to set unknown type
    Relationship rel;// = UNKNWON;
    Entity argOneType;// = UNKNWON;
    Entity argTwoType;// = UNKNWON;
    string argOne = "";
    string argTwo = "";
    bool validity = false;

    string extractArgOne(Relationship rel, string str);
    string extractArgTwo(string str);
};
