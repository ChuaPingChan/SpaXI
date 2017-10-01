#pragma once
#include <string>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\..\QueryTree.h"

class PatternValidator
{
public:
    static const string ASSIGN;
    static const string WHILE;
    static const string IF;

    static const string VARIABLE;
    static const string UNDERSCORE;
    static const string IDENT_WITH_QUOTES;
    static const string EXPRESSION_SPEC;

    PatternValidator(string patternType, string paramStr, QueryTree *qtPtrNew);
    ~PatternValidator();

    virtual void validate();
    virtual bool isValid();

    string getPatternType();
    string getArgOneType();
    string getArgTwoType();
    string getArgThreeType();
    string getArgOne();
    string getArgTwo();
    string getArgThree();

protected:
    QueryTree *qtPtr;
    string paramStr;

    string patternType;
    string argOneType;
    string argTwoType;
    string argThreeType;
    string argOne;
    string argTwo;
    string argThree;

    bool validity = false;

    
};

