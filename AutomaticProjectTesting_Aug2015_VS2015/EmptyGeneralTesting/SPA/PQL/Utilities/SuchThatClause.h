#pragma once
#include <string>
#include "../../Entity.h"
#include "../Relationship.h"

using namespace std;

class SuchThatClause
{
public:
    SuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo);
    ~SuchThatClause();

    /* Getters */
    Relationship getRel();
    Entity getArgOneType();
    Entity getArgTwoType();
    string getArgOne();
    string getArgTwo();

private:
    Relationship _rel;
    Entity _argOneType;
    Entity _argTwoType;
    string _argOne;
    string _argTwo;
};

