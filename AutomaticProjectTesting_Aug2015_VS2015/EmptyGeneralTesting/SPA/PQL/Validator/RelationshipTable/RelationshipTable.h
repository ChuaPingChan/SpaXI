#pragma once
#include"Relationship.h"
#include<unordered_map>

typedef string RELATION;
typedef string ARGTYPE;

class RelationshipTable
{
public:
    RelationshipTable();
    ~RelationshipTable();

    bool hasRelationship(RELATION);
    bool isArgValid(RELATION, ARGTYPE one, ARGTYPE two);
    bool isArgValid(RELATION, ARGTYPE one, ARGTYPE two, ARGTYPE three);

private:
    unordered_map<RELATION, Relationship> relTable;
};

