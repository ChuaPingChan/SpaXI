#pragma once
#include <string>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\QueryTree.h"

class PatternValidator
{
public:
    static const string PATTERN_KEYWORD;
    PatternValidator(PatternType patternType, string patternSyn, string paramStr, QueryTree *qtPtrNew);
    ~PatternValidator();

    virtual void validate();
    virtual bool isValid();

    PatternType getPatternType();
    Entity getArgOneType();
    Entity getArgTwoType();
    Entity getArgThreeType();
    string getPatternSynonym();
    string getArgOne();
    string getArgTwo();
    string getArgThree();

protected:
    static const int UNKNOWN = -1;
    QueryTree *qtPtr;
    string paramStr;

    //TODO: Might need unknown type
    PatternType patternType;// = UNKNOWN;
    Entity argOneType;// = UNKNOWN;
    Entity argTwoType;// = UNKNOWN;
    Entity argThreeType;// = UNKNOWN;
    string patternSyn = "";
    string argOne = "";
    string argTwo = "";
    string argThree = "";

    bool validity = false;
};
