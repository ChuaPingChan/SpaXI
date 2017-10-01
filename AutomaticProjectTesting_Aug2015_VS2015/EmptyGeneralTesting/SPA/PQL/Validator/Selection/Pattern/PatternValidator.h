#pragma once
#include <string>
#include "..\..\..\Utilities\Formatter.h"
#include "..\..\..\QueryTree.h"

class PatternValidator
{
public:
    PatternValidator(int patternType, string paramStr, QueryTree *qtPtrNew);
    ~PatternValidator();

    virtual void validate();
    virtual bool isValid();

    int getPatternType();
    int getArgOneType();
    int getArgTwoType();
    int getArgThreeType();
    string getArgOne();
    string getArgTwo();
    string getArgThree();

protected:
    QueryTree *qtPtr;
    string paramStr;

    int patternType;
    int argOneType;
    int argTwoType;
    int argThreeType;
    string argOne;
    string argTwo;
    string argThree;

    bool validity = false;
};
