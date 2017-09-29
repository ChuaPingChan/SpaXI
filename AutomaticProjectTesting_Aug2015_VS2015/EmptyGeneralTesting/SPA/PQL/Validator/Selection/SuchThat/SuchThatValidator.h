#pragma once
#include <string>
#include <unordered_set>
#include <regex>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\..\QueryTree.h"

using namespace std;

class SuchThatValidator
{
public:
    SuchThatValidator(QueryTree *qtPtrNew);
    SuchThatValidator();
    ~SuchThatValidator();

    virtual void validate();
    virtual bool isValid();

    string getRel();
    string getArgOneType();
    string getArgTwoType();
    string getArgOne();
    string getArgTwo();

protected:
    QueryTree *qtPtr;

    string rel;
    string argOneType;
    string argTwoType;
    string argOne;
    string argTwo;
    bool validity;

    string getArgOne(string keyword, string str);
    string getArgTwo(string str);

    bool isArgumentInClause(string arg, unordered_set<string> clause);

    //TODO: remove after implementing regex table
    bool isIntegerRegexCheck(string arg);
    bool isIdentWithInvertedCommas(string arg);
};
