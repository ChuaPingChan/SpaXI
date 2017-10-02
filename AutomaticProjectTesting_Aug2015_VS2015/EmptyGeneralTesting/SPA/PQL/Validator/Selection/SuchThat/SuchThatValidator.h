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
    SuchThatValidator(int rel, string paramStr, QueryTree *qtPtrNew);
    SuchThatValidator();
    ~SuchThatValidator();

    virtual void validate();
    virtual bool isValid();

    int getRel();
    int getArgOneType();
    int getArgTwoType();
    string getArgOne();
    string getArgTwo();

protected:
    static const int UNKNWON = -1;
    QueryTree *qtPtr;
    string paramStr;

    int rel = UNKNWON;
    int argOneType = UNKNWON;
    int argTwoType = UNKNWON;
    string argOne = "";
    string argTwo = "";
    bool validity = false;

    string extractArgOne(int rel, string str);
    string extractArgTwo(string str);
};
