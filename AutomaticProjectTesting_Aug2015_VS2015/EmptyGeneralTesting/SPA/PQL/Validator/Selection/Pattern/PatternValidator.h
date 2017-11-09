#pragma once
#include <string>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\ValidationRegexLibrary\RegexValidators.h"
#include "..\..\..\QueryTree.h"

/**
 * Super class of all pattern validators
 */
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
    QueryTree *qtPtr;
    string paramStr;

    PatternType patternType;
    Entity argOneType;
    Entity argTwoType;
    Entity argThreeType;
    string patternSyn;
    string argOne;
    string argTwo;
    string argThree;

    bool validity = false;
};
