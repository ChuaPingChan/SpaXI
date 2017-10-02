#pragma once
#include <string>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\QueryTree.h"

class PatternValidator
{
public:
    static const string PATTERN_KEYWORD;
    PatternValidator(int patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew);
    ~PatternValidator();

    virtual void validate();
    virtual bool isValid();

    int getPatternType();
    int getArgOneType();
    int getArgTwoType();
    int getArgThreeType();
    string getPatternSynonym();
    string getArgOne();
    string getArgTwo();
    string getArgThree();

protected:
    static const int UNKNOWN = -1;
    QueryTree *qtPtr;
    string paramStr;

    int patternType = UNKNOWN;
    int argOneType = UNKNOWN;
    int argTwoType = UNKNOWN;
    int argThreeType = UNKNOWN;
    string patternSyn = "";
    string argOne = "";
    string argTwo = "";
    string argThree = "";

    bool validity = false;
};
