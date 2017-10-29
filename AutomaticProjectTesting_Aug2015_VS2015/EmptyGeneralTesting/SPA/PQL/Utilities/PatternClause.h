#pragma once
#include <string>
#include "../../Entity.h"
#include "../Patternship.h"
#include "Clause.h"

using namespace std;

class PatternClause : public Clause
{
public:

    PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo);                                  //Asssign and While
    PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree);    //If
    ~PatternClause();

    /* Getters */
    PatternType getPatternType();
    Entity getArgOneType();
    Entity getArgTwoType();
    Entity getArgThreeType();
    string getPatternSynonym();
    string getArgOne();
    string getArgTwo();
    string getArgThree();

private:
    PatternType _patternType;
    Entity _argOneType;
    Entity _argTwoType;
    Entity _argThreeType;
    string _patternSyn;
    string _argOne;
    string _argTwo;
    string _argThree;
};
