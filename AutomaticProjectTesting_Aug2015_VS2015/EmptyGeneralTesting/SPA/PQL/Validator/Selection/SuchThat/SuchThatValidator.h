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
    static const string MODIFIES;
    static const string USES;
    static const string PARENT;
    static const string PARENTSTAR;
    static const string FOLLOWS;
    static const string FOLLOWSSTAR;
    static const string CALLS;
    static const string CALLSSTAR;
    static const string NEXT;
    static const string NEXTSTAR;
    static const string AFFECTS;
    static const string AFFECTSSTAR;

    static const string STMT;
    static const string ASSIGN;
    static const string WHILE;
    static const string IF;
    static const string PROG_LINE;
    static const string CALL;
    static const string PROCEDURE;
    static const string VARIABLE;
    static const string INTEGER;
    static const string UNDERSCORE;
    static const string IDENT_WITH_QUOTES;
    static const string CONSTANT;

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

    string extractArgOne(string keyword, string str);
    string extractArgTwo(string str);

    bool isArgumentInClause(string arg, unordered_set<string> clause);

    //TODO: remove after implementing regex table
    bool isIntegerRegexCheck(string arg);
    bool isIdentWithQuotes(string arg);
};
