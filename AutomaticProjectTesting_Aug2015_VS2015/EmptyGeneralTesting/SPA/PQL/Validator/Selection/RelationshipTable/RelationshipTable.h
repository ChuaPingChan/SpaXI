#pragma once
#include"Relationship.h"
#include<unordered_map>
#include<assert.h>
#include "EntityTable.h"

typedef int RELATION;
typedef int ARGTYPE;

class RelationshipTable
{
public:
    RelationshipTable();
    ~RelationshipTable();
    bool isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two);
    bool isArgValid(RELATION inputRel, ARGTYPE one, ARGTYPE two, ARGTYPE three);
    Relationship rModify, rUses, rParent, rParentStar, rFollows, rFollowsStar, rCalls, rCallsStar, rNext, rNextStar, rAffects, rAffectsStar, rPattern;

private:
    unordered_map<RELATION, Relationship> relTable;

    /****** Helper methods for Validity of Argument Type *******/
    bool isArg1Valid(Relationship rel, ARGTYPE arg1);
    bool isArg2Valid(Relationship rel, ARGTYPE arg);
    bool isArg3Valid(Relationship rel, ARGTYPE arg);
};

