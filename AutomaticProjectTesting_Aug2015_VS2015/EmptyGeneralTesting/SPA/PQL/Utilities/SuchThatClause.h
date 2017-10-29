#pragma once
#include <string>
#include "../../Entity.h"
#include "../Relationship.h"
#include "Clause.h"

using namespace std;

class SuchThatClause : public Clause
{
public:
    SuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo);
    SuchThatClause(SuchThatClause &suchThatClause);
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

